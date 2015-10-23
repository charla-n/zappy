/*
** manage_task.c for manage_task in /home/charla_n/projects/zappy/server/src
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Wed May 22 13:09:37 2013 nicolas charlas
** Last update Fri Jul 12 14:20:08 2013 nicolas charlas
*/

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include "server.h"

static int		end_task(t_srv *srv, t_client *client)
{
  struct timeval	t;

  gettimeofday(&t, NULL);
  if (client->type == FD_EGG)
    {
      gettimeofday(&client->ttl, NULL);
      client->ttl.tv_sec += DEFAULT_LIFE * 126 * 1 / srv->args.wait_time;
      client->action.has_task = -1;
      if (event_egg_opened(srv, client) == FAILURE)
	return (FAILURE);
      delete_egg(&srv->begin[client->position.x
			     + (srv->args.map_x * client->position.y)]);
      printf("\033[1;33mEgg is opened !\033[0m\n");
    }
  else
    {
      client->action.must_write++;
      client->cmd_waiting--;
      if (event_end_incantation(srv, client) == FAILURE)
	return (FAILURE);
      client->action.has_task = -1;
      return (call_parsing(srv, client));
    }
  return (SUCCESS);
}

static int		call_end_task(t_srv *srv, t_client *tmp)
{
  struct timeval	t;
  double		diff;

  gettimeofday(&t, NULL);
  diff = tmp->action.time_task.tv_sec - t.tv_sec
    + (double)tmp->action.time_task.tv_usec / 1000000.
    - (double)t.tv_usec / 1000000.;
  if (diff <= 0.)
    return (end_task(srv, tmp));
  return (SUCCESS);
}

int			manage_task(t_srv *srv, t_client *current)
{
  t_client		*tmp;
  int			ret;

  tmp = current;
  while (tmp)
    {
      if (tmp->type != FD_GRAPHIC &&
	  tmp->type != FD_SERVER && tmp->type != FD_FREE &&
	  tmp->action.has_task != -1)
	if ((ret = call_end_task(srv, tmp)) == FAILURE || ret == DISCONNECTION)
	  return (ret);
      if (tmp->type == FD_CLIENT && tmp->action.has_task == -1 &&
	  tmp->step_engage == 3 && !nb_request(&tmp->buff_circ_w))
	if ((ret = call_parsing(srv, tmp)) == FAILURE || ret == DISCONNECTION)
	  return (ret);
      if (tmp->type == FD_GRAPHIC)
	if ((ret = call_parsing(srv, tmp)) == FAILURE || ret == DISCONNECTION)
	  return (ret);
      tmp = tmp->next;
    }
  if (current != srv->views && current != srv->eggs)
    return (manage_task(srv, srv->views));
  return (SUCCESS);
}
