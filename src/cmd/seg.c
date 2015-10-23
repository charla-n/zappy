/*
** seg.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Thu Jun 20 16:07:35 2013 nicolas charlas
** Last update Wed Jul  3 21:27:58 2013 nicolas charlas
*/

#include "server.h"

int		seg(__attribute__((unused))t_srv *srv,
		    void *ptr, char *cmd1,
		    __attribute__((unused))char *cmd2)
{
  t_client	*tmp;
  t_graphic	*g;

  if (!cmd1)
    return (SUCCESS);
  g = (t_graphic *)ptr;
  tmp = g->graphic;
  while (tmp && g->length_graphic)
    {
      tmp->action.must_write++;
      if (write_circ(&tmp->buff_circ_w, "seg ") == FAILURE ||
	  write_circ(&tmp->buff_circ_w, cmd1) == FAILURE ||
	  write_circ(&tmp->buff_circ_w, DELIM) == FAILURE)
	return (FAILURE);
      tmp = tmp->next;
      g->length_graphic--;
    }
  return (SUCCESS);
}
