/*
** new_client.c for zappy in /home/charla_n/projects/zappy/server/src
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Tue May 14 16:47:27 2013 nicolas charlas
** Last update Fri Jul 12 14:50:42 2013 nicolas charlas
*/

#define _BSD_SOURCE

#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "server.h"

static void		init_client_inventory(t_client *client)
{
  int			i;

  i = 0;
  while (i < LAST)
    client->inventory[i++] = 0;
}

static void		bzero_circ(t_client *client)
{
  client->buff_circ_w.start = 0;
  client->buff_circ_r.start = 0;
  client->buff_circ_w.end = 0;
  client->buff_circ_r.end = 0;
}

static void		print_client_init(t_client *client)
{
  printf("\033[1;36mNew client %d at : x %d y %d\033[0m\n",
	 client->fd, client->position.x, client->position.y);
}

t_client		*init_client(t_client *client, t_srv *srv)
{
  client->id = -1;
  client->by = -1;
  client->step_engage = 0;
  client->action.must_write = 0;
  client->position.x = random() % srv->args.map_x;
  client->position.y = random() % srv->args.map_y;
  print_client_init(client);
  client->position.direction = NORTH;
  client->cmd_waiting = 0;
  client->level = DEFAULT_LVL;
  client->action.has_task = -1;
  client->incant = NULL;
  gettimeofday(&client->ttl, NULL);
  client->ttl.tv_sec += DEFAULT_LIFE * 126 * 1 / srv->args.wait_time;
  init_client_inventory(client);
  if (!client->buff_circ_r.tab && !client->buff_circ_w.tab)
    {
      if (initialize_circ(&client->buff_circ_r) == FAILURE)
	return (NULL);
      if (initialize_circ(&client->buff_circ_w) == FAILURE)
	return (NULL);
    }
  else
    bzero_circ(client);
  return (client);
}

int			new_client(t_srv *srv,
				   __attribute__((unused))t_client *client)
{
  int			client_socket;
  struct sockaddr_in	c_in;
  socklen_t		size;
  int			(*fct[2])(t_srv *, t_client *);
  t_client		*nc;
#ifdef EPOLL
  struct epoll_event	event;
#endif

  size = sizeof(c_in);
  if ((client_socket = accept(srv->fd_srv,
			      (struct sockaddr *)&c_in, &size)) == -1)
    return (FULL_CLIENT);
  fct[0] = &client_read;
  fct[1] = &client_write;
  if ((nc = init_client(put_in_list_client(client_socket, FD_CLIENT,
					   &srv->clients, fct), srv)) == NULL
      || engage_conversation(srv, nc, 0) == FAILURE)
    return (FAILURE);
#ifdef EPOLL
  event.data.ptr = nc;
  event.events = EPOLLIN | EPOLLET;
  epoll_ctl(srv->epollfd, EPOLL_CTL_ADD, client_socket, &event);
#endif
  return (SUCCESS);
}
