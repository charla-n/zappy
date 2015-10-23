/*
** smg.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Thu Jun 20 16:04:20 2013 nicolas charlas
** Last update Wed Jul  3 21:29:22 2013 nicolas charlas
*/

#include "server.h"

int		smg(__attribute__((unused))t_srv *srv,
		    void *ptr, char *cmd1,
		    __attribute__((unused))char *cmd2)
{
  t_graphic	*g;
  t_client	*tmp;

  if (!cmd1)
    return (SUCCESS);
  g = (t_graphic *)ptr;
  tmp = g->graphic;
  while (tmp)
    {
      if (tmp->type == FD_GRAPHIC)
	{
	  tmp->action.must_write++;
	  if (write_circ(&tmp->buff_circ_w, "smg ") == FAILURE ||
	      write_circ(&tmp->buff_circ_w, cmd1) == FAILURE ||
	      write_circ(&tmp->buff_circ_w, DELIM) == FAILURE)
	    return (FAILURE);
	}
      tmp = tmp->next;
      g->length_graphic--;
    }
  return (SUCCESS);
}
