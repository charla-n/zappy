/*
** epoll_loop.c for zappy in /home/bender/projects/zappy/server
** 
** Made by nicolas charlas
** Login   <bender@epitech.net>
** 
** Started on  Sat Jul  6 15:28:26 2013 nicolas charlas
** Last update Sat Jul 13 17:31:41 2013 nicolas charlas
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include "server.h"

#ifdef EPOLL

static int		disconnection_epoll(t_srv *srv, t_client *client)
{
  epoll_ctl(srv->epollfd, EPOLL_CTL_DEL, client->fd, NULL);
  if (client->type == FD_CLIENT)
    {
      if (event_player_die(srv, client) == FAILURE)
	return (FAILURE);
      close(client->fd);
      client->type = FD_FREE;
      client->fd = -1;
    }
  close(client->fd);
  if (client->type == FD_GRAPHIC)
    delete_client(&srv->views, &client);
  return (SUCCESS);
}

static int		epollin_epollout(struct epoll_event *events,
					 t_srv *srv, int i, int ret)
{
  if (events[i].events & EPOLLIN)
    {
      if ((ret = client_read(srv, (t_client *)events[i].data.ptr))
	  == DISCONNECTION)
	return (disconnection_epoll(srv, events[i].data.ptr));
      if (ret == FAILURE)
	return (FAILURE);
    }
  else if (events[i].events & EPOLLOUT)
    {
      if (((t_client *)events[i].data.ptr)->type == FD_CLIENT)
	{
	  if ((ret = client_write(srv, (t_client *)events[i].data.ptr))
	      == DISCONNECTION)
	    return (disconnection_epoll(srv, events[i].data.ptr));
	}
      else
	if ((ret = client_graphic_write(srv, (t_client *)events[i].data.ptr))
	    == DISCONNECTION)
	  return (disconnection_epoll(srv, events[i].data.ptr));
      if (ret == FAILURE)
	return (FAILURE);
    }
  return (SUCCESS);
}

static int		flaged_epoll(struct epoll_event *events,
				     t_srv *srv, int max)
{
  int			i;
  int			ret;

  i = 0;
  ret = 0;
  while (i < max)
    {
      if (events[i].data.fd == srv->fd_srv)
	{
	  if (new_client(srv, NULL) == FAILURE)
	    return (FAILURE);
	}
      else
	if (epollin_epollout(events, srv, i, ret) == FAILURE)
	  return (FAILURE);
      i++;
    }
  return (SUCCESS);
}

static int		initialize_epoll(t_srv *srv, t_client *current)
{
  t_client		*tmp;
  struct epoll_event	event;

  tmp = current;
  while (tmp)
    {
      if (tmp->type != FD_SERVER && tmp->fd != -1 && tmp->action.must_write)
	{
	  event.data.ptr = tmp;
	  event.events = EPOLLOUT | EPOLLIN | EPOLLET;
	  epoll_ctl(srv->epollfd, EPOLL_CTL_MOD, tmp->fd, &event);
	}
      else if (tmp->type != FD_SERVER && tmp->fd != -1)
	{
	  event.data.ptr = tmp;
	  event.events = EPOLLIN | EPOLLET;
	  epoll_ctl(srv->epollfd, EPOLL_CTL_MOD, tmp->fd, &event);
	}
      tmp = tmp->next;
    }
  if (current != srv->views)
    return (initialize_epoll(srv, srv->views));
  return (SUCCESS);
}

int			loop(t_srv *srv)
{
  int			res;
  int			max;
  struct timeval	t;
  struct epoll_event	events[1024];

  res = 0;
  while (res != -1)
    {
      if (initialize_epoll(srv, srv->clients) == FAILURE)
	return (FAILURE);
      t.tv_sec = generate_elements(srv, &res);
      if (res == -1)
	return (FAILURE);
      get_time(&t, srv);
      if ((max = epoll_wait(srv->epollfd, events, 1024,
			    t.tv_sec * 1000)) == -1)
	return (FAILURE);
      if (flaged_epoll(events, srv, max) == FAILURE)
	return (FAILURE);
      if (do_manage(srv) == FAILURE)
	return (FAILURE);
    }
  return (res == -1 ? FAILURE : SUCCESS);
}
#endif
