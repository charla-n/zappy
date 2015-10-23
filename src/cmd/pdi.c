/*
** pgt.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Thu Jun 20 15:43:20 2013 nicolas charlas
** Last update Mon Jul  8 15:33:18 2013 nicolas charlas
*/

#define _BSD_SOURCE
#include <strings.h>
#include <stdio.h>
#include "server.h"

int		pdi(__attribute__((unused))t_srv *srv, void *ptr,
		    __attribute__((unused))char *cmd1,
		    __attribute__((unused))char *cmd2)
{
  t_graphic	*g;
  t_client	*tmp;
  char		buff[13];

  g = (t_graphic *)ptr;
  tmp = g->graphic;
  bzero(buff, 13);
  sprintf(buff, "%d", ((t_client *)g->players)->fd);
  while (tmp && g->length_graphic)
    {
      if (tmp->type == FD_GRAPHIC)
	{
	  tmp->action.must_write++;
	  if (write_circ(&tmp->buff_circ_w, "pdi ") == FAILURE ||
	      write_circ(&tmp->buff_circ_w, buff) == FAILURE ||
	      write_circ(&tmp->buff_circ_w, DELIM) == FAILURE)
	    return (FAILURE);
	}
      tmp = tmp->next;
      g->length_graphic--;
    }
  return (SUCCESS);
}
