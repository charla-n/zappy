/*
** event_end_incantation.c for zappy in /home/bender/projects/zappy/server
** 
** Made by nicolas charlas
** Login   <bender@epitech.net>
** 
** Started on  Mon Jul  8 12:51:59 2013 nicolas charlas
** Last update Fri Jul 12 14:32:29 2013 nicolas charlas
*/

#define _GNU_SOURCE
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"

static int	event_incantation_end(t_client *client,
				      t_srv *srv,
				      t_graphic g)
{
  int		i;
  char		buff[11];
  char		buff2[11];

  i = 0;
  bzero(buff, 11);
  bzero(buff2, 11);
  while (client->incant[i])
    {
      g.graphic = srv->views;
      g.length_graphic = -1;
      sprintf(buff, "%d", client->incant[i]->fd);
      if (plv(srv, &g, buff, NULL) == FAILURE)
	return (FAILURE);
      i++;
    }
  g.graphic = srv->views;
  g.length_graphic = -1;
  sprintf(buff, "%d", client->incant[0]->position.x);
  sprintf(buff2, "%d", client->incant[0]->position.y);
  return (bct(srv, &g, buff, buff2));
}

int		event_end_incantation(t_srv *srv, t_client *client)
{
  t_graphic	g;

  if (client->action.has_task != -1 &&
      client->action.duration == 300 && client->incant)
    {
      g.graphic = srv->views;
      g.length_graphic = -1;
      g.players = client;
      if (pie(srv, &g, client->result == 1 ? "1" : "0", NULL) == FAILURE)
	return (FAILURE);
      if (event_incantation_end(client, srv, g) == FAILURE)
	return (FAILURE);
      free(client->incant);
      client->incant = NULL;
    }
  return (SUCCESS);
}
