/*
** enw.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Fri Jun 21 12:20:18 2013 nicolas charlas
** Last update Thu Jul  4 15:59:03 2013 arthur jansen
*/

#define _BSD_SOURCE
#include <strings.h>
#include <stdio.h>
#include "server.h"

static int	enw_send_to_client(t_client *client, t_graphic *g,
				   t_client *tmp)
{
  char		buff[48];

  bzero(buff, 48);
  while (client && g->length_players)
    {
      sprintf(buff, "%d %d %d %d", client->id, client->by,
	      client->position.x, client->position.y);
      tmp->action.must_write++;
      if (write_circ(&tmp->buff_circ_w, "enw ") == FAILURE ||
	  write_circ(&tmp->buff_circ_w, buff) == FAILURE ||
	  write_circ(&tmp->buff_circ_w, DELIM) == FAILURE)
	return (FAILURE);
      client = client->next;
      g->length_players--;
    }
  return (SUCCESS);
}

int		enw(__attribute__((unused))t_srv *srv, void *ptr,
		    __attribute__((unused))char *cmd1,
		    __attribute__((unused))char *cmd2)
{
  t_graphic	*g;
  t_client	*tmp;
  t_client	*client;

  g = (t_graphic *)ptr;
  tmp = (t_client *)g->graphic;
  while (tmp && g->length_graphic)
    {
      client = (t_client *)g->players;
      if (tmp->type == FD_GRAPHIC)
	{
	  if (enw_send_to_client(client, g, tmp) == FAILURE)
	    return (FAILURE);
	}
      tmp = tmp->next;
      g->length_graphic--;
    }
  return (SUCCESS);
}
