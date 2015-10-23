/*
** pex.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Wed Jun 12 15:57:10 2013 nicolas charlas
** Last update Thu Jul  4 16:24:16 2013 arthur jansen
*/

#include <strings.h>
#include <stdio.h>
#include "server.h"

int		pex(__attribute__((unused))t_srv *srv, void *ptr,
		    __attribute__((unused))char *cmd1,
		    __attribute__((unused))char *cmd2)
{
  t_graphic	*g;
  char		buff[11];
  t_client	*v;

  g = (t_graphic *)ptr;
  v = g->graphic;
  bzero(buff, 11);
  sprintf(buff, "%d", ((t_client *)(g->players))->fd);
  while (v && g->length_graphic)
    {
      if (v->type == FD_GRAPHIC)
	{
	  v->action.must_write++;
	  if (write_circ(&v->buff_circ_w, "pex ") == FAILURE ||
	      write_circ(&v->buff_circ_w, buff) == FAILURE ||
	      write_circ(&v->buff_circ_w, DELIM) == FAILURE)
	    return (FAILURE);
	}
      v = v->next;
      g->length_graphic--;
    }
  return (SUCCESS);
}
