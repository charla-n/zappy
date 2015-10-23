/*
** broadcast.c for zappy in /home/jansen_a/svn/zappy/server
** 
** Made by arthur jansen
** Login   <jansen_a@epitech.net>
** 
** Started on  Mon Jun 24 14:16:26 2013 arthur jansen
** Last update Fri Jul 12 16:17:40 2013 caroline trompf
*/

#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

static int		broadcast_client(t_srv *srv, t_client *client,
					 int casenum, char *cmd1)
{
  char			*buffer;

  (void)srv;
  client->action.must_write++;
  if (asprintf(&buffer, "message %d,%s\n", casenum, cmd1) == -1)
    return (FAILURE);
  if (write_circ(&client->buff_circ_w, buffer) == FAILURE)
    return (FAILURE);
  if (write_circ(&client->buff_circ_w, DELIM) == FAILURE)
    return (FAILURE);
  free(buffer);
  return (SUCCESS);
}

static void		init_graph_player(t_graphic *graph, t_srv *srv,
					  t_client * client)
{
  graph->graphic = srv->views;
  graph->length_graphic = -1;
  graph->length_players = -1;
  graph->players = client;
}

static int		run_broadcast(t_srv *srv, t_client *client,
				      t_client *tmp, char *cmd1)
{
  int			direction;

  while (tmp != NULL)
    {
      if (tmp->type == FD_CLIENT)
        {
	  if (tmp->fd != client->fd
	      && tmp->position.x == client->position.x
	      && tmp->position.y == client->position.y)
	    {
	      if (broadcast_client(srv, tmp, 0, cmd1) == FAILURE)
		return (FAILURE);
	    }
	  else if (tmp->fd != client->fd)
	    {
	      if ((direction = search_bro_direction(client, tmp, srv))
		  == FAILURE)
		return (FAILURE);
	      if (broadcast_client(srv, tmp, direction, cmd1) == FAILURE)
		return (FAILURE);
	    }
	}
      tmp = tmp->next;
    }
  return (SUCCESS);
}

int			broadcast(t_srv *srv, void *ptr, char *cmd1,
				  __attribute__((unused))char *cmd2)
{
  t_client		*client;
  t_graphic		graph;
  t_client		*tmp;

  client = (t_client *)ptr;
  init_graph_player(&graph, srv, client);
  if (pbc(srv, &graph, cmd1, cmd2) == FAILURE)
    return (FAILURE);
  init_time_task(srv, client, 7);
  tmp = srv->clients;
  run_broadcast(srv, client, tmp, cmd1);
  if (write_circ(&client->buff_circ_w, "ok"DELIM) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}
