/*
** pfk.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Thu Jun 13 17:18:44 2013 nicolas charlas
** Last update Wed Jul  3 19:50:36 2013 nicolas charlas
*/

#include <stdio.h>
#include <strings.h>
#include "server.h"

int		pfk(__attribute__((unused))t_srv *srv, void *ptr,
		    __attribute__((unused))char *cmd1,
		    __attribute__((unused))char *cmd2)
{
  t_graphic	*g;
  t_client	*tmp;
  t_client	*client;
  char		buff[12];

  g = (t_graphic *)ptr;
  tmp = g->graphic;
  client = (t_client *)(g->players);
  bzero(buff, 12);
  sprintf(buff, "%d", client->fd);
  while (tmp && g->length_graphic)
    {
      if (tmp->type == FD_GRAPHIC)
	{
	  tmp->action.must_write++;
	  if (write_circ(&tmp->buff_circ_w, "pfk ") == FAILURE ||
	      write_circ(&tmp->buff_circ_w, buff) == FAILURE ||
	      write_circ(&tmp->buff_circ_w, DELIM) == FAILURE)
	    return (FAILURE);
	}
      tmp = tmp->next;
      g->length_graphic--;
    }
  return (SUCCESS);
}
