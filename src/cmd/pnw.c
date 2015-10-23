/*
** pnw.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Wed Jun 12 15:13:10 2013 nicolas charlas
** Last update Thu Jul  4 14:28:31 2013 nicolas charlas
*/

#include <stdio.h>
#include <strings.h>
#include "server.h"

static int	pnw_send_to_client(t_client *client, char *buff, int last,
				   t_graphic *g)
{
  t_client	*tmp;

  tmp = g->graphic;
  if (client->type == FD_CLIENT && client->team)
    {
      sprintf(buff, "%d %d %d %d %d %s", client->fd, client->position.x,
	      client->position.y, client->position.direction + 1,
	      client->level, client->team->name);
      tmp = g->graphic;
      g->length_graphic = last;
      while (tmp && g->length_graphic)
	{
	  if (tmp->type == FD_GRAPHIC)
	    {
	      tmp->action.must_write++;
	      if (write_circ(&tmp->buff_circ_w, "pnw ") == FAILURE ||
		  write_circ(&tmp->buff_circ_w, buff) == FAILURE ||
		  write_circ(&tmp->buff_circ_w, DELIM) == FAILURE)
		return (FAILURE);
	    }
	  tmp = tmp->next;
	  g->length_graphic--;
	}
    }
  return (SUCCESS);
}

int		pnw(__attribute__((unused))t_srv *srv, void *ptr,
		    __attribute__((unused))char *cmd1,
		    __attribute__((unused))char *cmd2)
{
  t_graphic	*g;
  char		buff[285];
  t_client	*client;
  int		last;

  g = (t_graphic *)ptr;
  last = g->length_graphic;
  bzero(buff, 285);
  client = (t_client *)(g->players);
  while (client && g->length_players)
    {
      if (pnw_send_to_client(client, buff, last, g) == FAILURE)
	return (FAILURE);
      client = client->next;
      g->length_players--;
    }
  return (SUCCESS);
}
