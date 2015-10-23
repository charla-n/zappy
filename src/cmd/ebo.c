/*
** ebo.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Fri Jun 21 12:11:29 2013 nicolas charlas
** Last update Wed Jul  3 19:08:58 2013 nicolas charlas
*/

#define _BSD_SOURCE
#include <stdio.h>
#include <strings.h>
#include "server.h"

int		ebo(t_srv *srv, void *ptr, char *cmd1, char *cmd2)
{
  char		buff[11];
  t_graphic	*g;
  t_client	*tmp;

  (void)srv;
  (void)cmd1;
  (void)cmd2;
  g = (t_graphic *)ptr;
  bzero(buff, 11);
  sprintf(buff, "%d", ((t_client *)g->players)->id);
  tmp = g->graphic;
  while (tmp && g->length_graphic)
    {
      if (tmp->type == FD_GRAPHIC)
	{
	  tmp->action.must_write++;
	  if (write_circ(&tmp->buff_circ_w, "ebo ") == FAILURE ||
	      write_circ(&tmp->buff_circ_w, buff) == FAILURE ||
	      write_circ(&tmp->buff_circ_w, DELIM) == FAILURE)
	    return (FAILURE);
	}
      tmp = tmp->next;
      g->length_graphic--;
    }
  return (SUCCESS);
}
