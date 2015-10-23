/*
** ppo.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Tue Jun 11 21:28:29 2013 nicolas charlas
** Last update Sat Jul 13 16:37:05 2013 arthur jansen
*/

#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

static int	plv_send_to_client(t_srv *srv, t_client *v,
				   int num_player, char *buff)
{
  t_client	*tmp;

  tmp = srv->clients;
  if (v->type == FD_GRAPHIC)
    {
      while (tmp)
	{
	  if (tmp->fd == num_player && tmp->type == FD_CLIENT)
	    {
	      v->action.must_write++;
	      sprintf(buff, "%d %d", tmp->fd, tmp->level);
	      if (write_circ(&v->buff_circ_w, "plv ") == FAILURE ||
		  write_circ(&v->buff_circ_w, buff) == FAILURE ||
		  write_circ(&v->buff_circ_w, DELIM) == FAILURE)
		return (FAILURE);
	      return (SUCCESS);
	    }
	  tmp = tmp->next;
	}
    }
  return (FAILURE);
}

int		plv(t_srv *srv, void *ptr, char *cmd1,
		    __attribute__((unused))char *cmd2)
{
  t_graphic	*g;
  char		buff[21];
  t_client	*v;
  int		num_player;

  g = (t_graphic *)ptr;
  v = g->graphic;
  if (!cmd1)
    return (sbp(g->graphic));
  num_player = atoi(cmd1);
  bzero(buff, 21);
  while (v && g->length_graphic)
    {
      if (plv_send_to_client(srv, v, num_player, buff) == FAILURE)
	return (FAILURE);
      v = v->next;
      g->length_graphic--;
    }
  return (SUCCESS);
}
