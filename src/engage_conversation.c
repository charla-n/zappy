/*
** engage_conversation.c for engage_conversation in /home/charla_n/projects/zappy/server/src
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Sat May 18 12:56:43 2013 nicolas charlas
** Last update Fri Jul  5 14:31:14 2013 nicolas charlas
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <strings.h>
#include <stdlib.h>
#include "server.h"

static int	first_engage(t_client *nc)
{
  if (write_circ(&nc->buff_circ_w, MESSAGE_1) == FAILURE)
    return (FAILURE);
  if (write_circ(&nc->buff_circ_w, DELIM) == FAILURE)
    return (FAILURE);
  nc->action.must_write++;
  nc->step_engage++;
  return (SUCCESS);
}

static int	connect_to_fork(t_srv *srv, t_client *nc, char *ask)
{
  t_client	*tmp;

  tmp = srv->eggs;
  while (tmp)
    {
      if (!strcmp(tmp->team->name, ask) && tmp->action.has_task == -1)
	{
	  if (event_egg(srv, tmp) == FAILURE)
	    return (-2);
	  nc->position.x = tmp->position.x;
	  nc->position.y = tmp->position.y;
	  nc->position.direction = tmp->position.direction;
	  nc->type = FD_CLIENT;
	  delete_client(&srv->eggs, &tmp);
	  printf("\033[1;33mClient is connecting on an egg\033[0m\n");
	  return (SUCCESS);
	}
      tmp = tmp->next;
    }
  return (FAILURE);
}

static int	client_is_player(t_srv *srv, t_client *nc, char *ask)
{
  int		ret;
  t_team	*tmp;
  char		buff[BUFFER_SIZE];

  tmp = srv->args.team;
  while (tmp && strcmp(ask, tmp->name))
    tmp = tmp->next;
  if (!tmp || ((ret = connect_to_fork(srv, nc, ask)) == FAILURE &&
	       tmp->nb_client == 0))
    return (DISCONNECTION);
  if (ret == -2)
    return (FAILURE);
  nc->team = tmp;
  tmp->nb_client--;
  nc->action.must_write += 2;
  bzero(buff, BUFFER_SIZE);
  sprintf(buff, "%d"DELIM, tmp->nb_client);
  if (write_circ(&nc->buff_circ_w, buff) == FAILURE)
    return (FAILURE);
  bzero(buff, BUFFER_SIZE);
  sprintf(buff, "%d %d"DELIM, srv->args.map_x, srv->args.map_y);
  if (write_circ(&nc->buff_circ_w, buff) == FAILURE)
    return (FAILURE);
  nc->step_engage++;
  return (event_player_connection(srv, nc));
}

static int	client_is_graphic(t_srv *srv, t_client *nc)
{
  t_client	*tmp;

  tmp = srv->clients;
  while (tmp && tmp->next != nc)
    tmp = tmp->next;
  nc->type = FD_GRAPHIC;
  tmp->next = nc->next;
  tmp = srv->views;
  nc->next = NULL;
  nc->write_func = client_graphic_write;
  while (tmp && tmp->next)
    tmp = tmp->next;
  if (tmp)
    tmp->next = nc;
  else
    srv->views = nc;
  return (events_graphic_connection(srv, nc));
}

int		engage_conversation(t_srv *srv, t_client *nc, char *ask)
{
  if (nc->step_engage == 0)
    {
      if (first_engage(nc) == FAILURE)
	return (FAILURE);
    }
  else if (nc->step_engage == 1)
    {
      if (!strcmp(ask, MESSAGE_GRAPH))
	return (client_is_graphic(srv, nc));
      else
	return (client_is_player(srv, nc, ask));
    }
  return (SUCCESS);
}
