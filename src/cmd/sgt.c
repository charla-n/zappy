/*
** sgt.c for sgt in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Wed Jun 19 11:04:09 2013 nicolas charlas
** Last update Wed Jul  3 21:28:53 2013 nicolas charlas
*/

#define _BSD_SOURCE
#include <stdio.h>
#include <strings.h>
#include "server.h"

int		sgt(t_srv *srv, void *ptr,
		    __attribute__((unused))char *cmd1,
		    __attribute__((unused))char *cmd2)
{
  t_graphic	*g;
  t_client	*tmp;
  char		buff[17];

  g = (t_graphic *)ptr;
  tmp = g->graphic;
  bzero(buff, 16);
  sprintf(buff, "sgt %d"DELIM, srv->args.wait_time);
  while (g->length_graphic && tmp)
    {
      if (tmp->type == FD_GRAPHIC)
	{
	  if (write_circ(&tmp->buff_circ_w, buff) == FAILURE)
	    return (FAILURE);
	  tmp->action.must_write++;
	}
      tmp = tmp->next;
      g->length_graphic--;
    }
  return (SUCCESS);
}
