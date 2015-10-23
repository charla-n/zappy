/*
** msz.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Tue Jun 11 17:33:21 2013 nicolas charlas
** Last update Thu Jul  4 16:19:31 2013 arthur jansen
*/

#include <stdio.h>
#include <strings.h>
#include "server.h"

int		msz(t_srv *srv, void *ptr,
		    __attribute__((unused))char *cmd1,
		    __attribute__((unused))char *cmd2)
{
  t_graphic	*g;
  t_client	*tmp;
  char		buff[13];

  g = (t_graphic *)ptr;
  bzero(buff, 13);
  sprintf(buff, "msz %d %d"DELIM, srv->args.map_x, srv->args.map_y);
  tmp = g->graphic;
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
