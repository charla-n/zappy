/*
** connect_to.c for connect_to in /home/charla_n/projects/zappy/server/src
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Thu May  9 17:34:03 2013 nicolas charlas
** Last update Sat Jul  6 17:28:41 2013 nicolas charlas
*/

#include <netdb.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

static t_client	*get_old_client(int fd, int type, t_client **client,
				int (*fct[2])(t_srv *srv, t_client *))
{
  t_client	*tmp;

  tmp = *client;
  while (tmp && tmp->type != FD_FREE)
    tmp = tmp->next;
  if (!tmp)
    return (NULL);
  printf("\033[1;31mConnecting client to an old client\033[0m\n");
  tmp->team = NULL;
  tmp->fd = fd;
  tmp->type = type;
  tmp->read_func = fct[0];
  tmp->write_func = fct[1];
  return (tmp);
}

t_client	*put_in_list_client(int fd, int type, t_client **client,
				    int (*fct[2])(t_srv *srv, t_client *))
{
  t_client	*tmp;
  t_client	*elem;

  if (type != FD_EGG && (tmp = get_old_client(fd, type, client, fct)))
    return (tmp);
  if ((elem = malloc(sizeof(t_client))) == NULL)
    return (NULL);
  printf("\033[1;31mConnecting client at a new instance of client\033[0m\n");
  elem->team = NULL;
  elem->fd = fd;
  elem->type = type;
  elem->read_func = fct[0];
  elem->write_func = fct[1];
  elem->next = NULL;
  elem->buff_circ_w.tab = NULL;
  elem->buff_circ_r.tab = NULL;
  if (*client == NULL)
    return ((*client = elem));
  tmp = *client;
  while (tmp && tmp->next)
    tmp = tmp->next;
  tmp->next = elem;
  return (elem);
}

static int	init_co(t_srv *srv)
{
  int		(*fct[2])(t_srv *srv, t_client *);

#ifdef EPOLL
  (void)fct;
  srv->event.events = EPOLLIN | EPOLLET;
  srv->event.data.fd = srv->fd_srv;
  if (epoll_ctl(srv->epollfd, EPOLL_CTL_ADD, srv->fd_srv, &srv->event) == -1)
    return (write_error("connect_to(epoll_ctl) ", srv->fd_srv));
#endif
  fct[0] = &new_client;
  fct[1] = NULL;
  if (put_in_list_client(srv->fd_srv, FD_SERVER, &srv->clients,
			 fct) == NULL)
    return (FAILURE);
  return (SUCCESS);
}

int			connect_to(t_srv *srv)
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  int			fd_sock;
  int			ok;

#ifdef EPOLL
  if ((srv->epollfd = epoll_create1(0)) == -1)
    return (FAILURE);
#endif
  ok = 1;
  if ((pe = getprotobyname("TCP")) == NULL)
    return (write_error("connect_to(getprotobyname) ", -1));
  if ((fd_sock = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (write_error("connect_to(socket) ", -1));
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(srv->args.port);
  s_in.sin_addr.s_addr = INADDR_ANY;
  if (setsockopt(fd_sock, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(int)) == -1)
    return (write_error("connect_to(setsockopt) ", fd_sock));
  if (bind(fd_sock, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    return (write_error("connect_to(bind) ", fd_sock));
  if (listen(fd_sock, QUEUE) == -1)
    return (write_error("connect_to(listen) ", fd_sock));
  srv->fd_srv = fd_sock;
  return (init_co(srv));
}
