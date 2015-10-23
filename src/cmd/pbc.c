/*
** pbc.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Wed Jun 12 18:46:33 2013 nicolas charlas
** Last update Wed Jul 10 19:52:49 2013 nicolas charlas
*/

#include <strings.h>
#include <stdio.h>
#include "server.h"

int		pbc(__attribute__((unused))t_srv *srv,
		    void *ptr, char *cmd1,
		    __attribute__((unused))char *cmd2)
{
  t_graphic	*g;
  char		buff[1040];
  t_client	*tmp;

  g = (t_graphic *)ptr;
  if (!cmd1)
    return (SUCCESS);
  tmp = g->graphic;
  bzero(buff, 1040);
  sprintf(buff, "%d %s", ((t_client *)(g->players))->fd, cmd1);
  while (tmp && g->length_graphic)
    {
      if (tmp->type == FD_GRAPHIC)
	{
	  tmp->action.must_write++;
	  if (write_circ(&tmp->buff_circ_w, "pbc ") == FAILURE ||
	      write_circ(&tmp->buff_circ_w, buff) == FAILURE ||
	      write_circ(&tmp->buff_circ_w, DELIM) == FAILURE)
	    return (FAILURE);
	}
      tmp = tmp->next;
      g->length_graphic--;
    }
  return (SUCCESS);
}
