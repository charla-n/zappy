/*
** tna.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Tue Jun 11 21:16:47 2013 nicolas charlas
** Last update Wed Jul  3 21:31:48 2013 nicolas charlas
*/

#include "server.h"

int		tna(t_srv *srv, void *ptr,
		    __attribute__((unused))char *cmd1,
		    __attribute__((unused))char *cmd2)
{
  t_graphic	*g;
  t_client	*c;
  t_team	*tmp;

  g = (t_graphic *)ptr;
  c = g->graphic;
  while (c && g->length_graphic)
    {
      tmp = srv->args.team;
      if (c->type == FD_GRAPHIC)
	{
	  while (tmp)
	    {
	      c->action.must_write++;
	      if (write_circ(&c->buff_circ_w, "tna ") == FAILURE ||
		  write_circ(&c->buff_circ_w, tmp->name) == FAILURE ||
		  write_circ(&c->buff_circ_w, DELIM) == FAILURE)
		return (FAILURE);
	      tmp = tmp->next;
	    }
	}
      c = c->next;
      g->length_graphic--;
    }
  return (SUCCESS);
}
