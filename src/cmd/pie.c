/*
** pie.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Thu Jun 20 14:29:18 2013 nicolas charlas
** Last update Wed Jul  3 20:06:14 2013 nicolas charlas
*/

#define _BSD_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "server.h"

static int	send_pie(t_client *tmp, char *buff)
{
  tmp->action.must_write++;
  if (write_circ(&tmp->buff_circ_w, "pie ") == FAILURE ||
      write_circ(&tmp->buff_circ_w, buff) == FAILURE ||
      write_circ(&tmp->buff_circ_w, DELIM) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}

int		pie(__attribute__((unused))t_srv *srv,
		    void *ptr, char *cmd1,
		    __attribute__((unused))char *cmd2)
{
  char		buff[10];
  t_graphic	*g;
  t_client	*tmp;
  t_client	*client;

  g = (t_graphic *)ptr;
  if (!cmd1)
    return (SUCCESS);
  tmp = g->graphic;
  bzero(buff, 10);
  client = (t_client *)(g->players);
  sprintf(buff, "%d %d %s", client->position.x, client->position.y, cmd1);
  while (tmp && g->length_graphic)
    {
      if (tmp->type == FD_GRAPHIC)
	{
	  if (send_pie(tmp, buff) == FAILURE)
	    return (FAILURE);
	}
      tmp = tmp->next;
      g->length_graphic--;
    }
  return (SUCCESS);
}
