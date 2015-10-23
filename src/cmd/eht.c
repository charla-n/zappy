/*
** eht.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Fri Jun 21 12:11:29 2013 nicolas charlas
** Last update Thu Jul  4 15:57:48 2013 arthur jansen
*/

#define _BSD_SOURCE
#include <stdio.h>
#include <strings.h>
#include "server.h"

int		eht(__attribute__((unused))t_srv *srv, void *ptr,
		    __attribute__((unused))char *cmd1,
		    __attribute__((unused))char *cmd2)
{
  char		buff[11];
  t_graphic	*g;
  t_client	*tmp;

  g = (t_graphic *)ptr;
  bzero(buff, 11);
  sprintf(buff, "%d", ((t_client *)g->players)->id);
  tmp = g->graphic;
  while (tmp && g->length_graphic)
    {
      if (tmp->type == FD_GRAPHIC)
	{
	  tmp->action.must_write++;
	  if (write_circ(&tmp->buff_circ_w, "eht ") == FAILURE ||
	      write_circ(&tmp->buff_circ_w, buff) == FAILURE ||
	      write_circ(&tmp->buff_circ_w, DELIM) == FAILURE)
	    return (FAILURE);
	}
      tmp = tmp->next;
      g->length_graphic--;
    }
  return (SUCCESS);
}
