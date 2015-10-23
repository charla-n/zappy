/*
** processing_flags.c for zappy in /home/bender/projects/zappy/server
** 
** Made by nicolas charlas
** Login   <bender@epitech.net>
** 
** Started on  Wed Jul  3 12:21:22 2013 nicolas charlas
** Last update Sat Jul  6 15:30:12 2013 nicolas charlas
*/

#include <unistd.h>
#include <sys/select.h>
#include "server.h"

#ifndef EPOLL
static void	init_fd(t_client *current, t_srv *srv)
{
  if (current == srv->clients)
    {
      FD_ZERO(&srv->read);
      FD_ZERO(&srv->write);
    }
}
#endif

#ifndef EPOLL
void		initialize(t_srv *srv, int *max, int *has_data_write,
			   t_client *current)
{
  t_client	*tmp;

  init_fd(current, srv);
  tmp = current;
  while (tmp)
    {
      if (tmp->type != FD_FREE)
	{
	  FD_SET(tmp->fd, &srv->read);
	  if (tmp->type != FD_SERVER && tmp->fd != -1 &&
	      tmp->action.must_write)
	    {
	      *has_data_write = 1;
	      FD_SET(tmp->fd, &srv->write);
	    }
	  if (tmp->fd > *max)
	    *max = tmp->fd;
	}
      tmp = tmp->next;
    }
  if (current == srv->clients)
    initialize(srv, max, has_data_write, srv->views);
}
#endif

#ifndef EPOLL
static int	do_disconnection(t_srv *srv, t_client **tmp,
				 char *delete)
{
  if ((*tmp)->type == FD_CLIENT)
    {
      if (event_player_die(srv, *tmp) == FAILURE)
	return (FAILURE);
      close((*tmp)->fd);
      (*tmp)->type = FD_FREE;
      (*tmp)->fd = -1;
    }
  close((*tmp)->fd);
  if ((*tmp)->type == FD_GRAPHIC)
    {
      *delete = 1;
      delete_client(&srv->views, tmp);
    }
  return (SUCCESS);
}
#endif

#ifndef EPOLL
static int	process_flaged(t_srv *srv, t_client **tmp, char *delete)
{
  int		ret;

  if (FD_ISSET((*tmp)->fd, &srv->read))
    {
      if ((ret = (*tmp)->read_func(srv, *tmp)) == DISCONNECTION)
	{
	  if (do_disconnection(srv, tmp, delete) == FAILURE)
	    return (FAILURE);
	}
      if (ret == FAILURE)
	return (FAILURE);
    }
  if (*tmp && (*tmp)->write_func && FD_ISSET((*tmp)->fd, &srv->write))
    {
      if ((ret = (*tmp)->write_func(srv, *tmp)) == DISCONNECTION)
	{
	  if (do_disconnection(srv, tmp, delete) == FAILURE)
	    return (FAILURE);
	}
      if (ret == FAILURE)
	return (FAILURE);
    }
  return (SUCCESS);
}
#endif

#ifndef EPOLL
int		is_flaged(t_srv *srv, t_client *current)
{
  t_client	*tmp;
  char		delete;

  tmp = current;
  while (tmp)
    {
      delete = 0;
      if (process_flaged(srv, &tmp, &delete) == FAILURE)
	return (FAILURE);
      if (!delete)
	tmp = tmp->next;
    }
  if (current != srv->views)
    return (is_flaged(srv, srv->views));
  return (SUCCESS);
}
#endif
