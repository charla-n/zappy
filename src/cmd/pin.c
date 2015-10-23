/*
** pin.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Wed Jun 12 15:31:57 2013 nicolas charlas
** Last update Wed Jul  3 21:45:18 2013 nicolas charlas
*/

#include <sys/time.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include "server.h"

static int		send_pin(t_client *v, char *buff)
{
  if (write_circ(&v->buff_circ_w, "pin ") == FAILURE ||
      write_circ(&v->buff_circ_w, buff) == FAILURE ||
      write_circ(&v->buff_circ_w, DELIM) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}

static int		pin_send_to_client(t_srv *srv, int client_asked,
					   t_client *v, char *buff)
{
  t_client		*tmp;
  struct timeval	t;

  tmp = srv->clients;
  if (v->type == FD_GRAPHIC)
    {
      while (tmp)
	{
	  if (tmp->fd == client_asked && tmp->type == FD_CLIENT)
	    {
	      v->action.must_write++;
	      gettimeofday(&t, NULL);
	      sprintf(buff, "%d %d %d %d %d %d %d %d %d %d", tmp->fd,
		      tmp->position.x, tmp->position.y,
		      (int)(tmp->ttl.tv_sec - t.tv_sec),
		      tmp->inventory[LINEMATE], tmp->inventory[DERAUMERE],
		      tmp->inventory[SIBUR], tmp->inventory[MENDIANE],
		      tmp->inventory[PHIRAS], tmp->inventory[THYSTAME]);
	      if (send_pin(v, buff) == FAILURE)
		return (FAILURE);
	    }
	  tmp = tmp->next;
	}
    }
  return (SUCCESS);
}

int			pin(t_srv *srv, void *ptr, char *cmd1,
			    __attribute__((unused))char *cmd2)
{
  t_graphic		*g;
  char			buff[100];
  t_client		*v;
  int			client_asked;

  g = (t_graphic *)ptr;
  v = g->graphic;
  if (!cmd1)
    return (sbp(g->graphic));
  client_asked = atoi(cmd1);
  bzero(buff, 100);
  while (v && g->length_graphic)
    {
      if (pin_send_to_client(srv, client_asked, v, buff) == FAILURE)
	return (FAILURE);
      v = v->next;
      g->length_graphic--;
    }
  return (SUCCESS);
}
