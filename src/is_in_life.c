/*
** is_in_life.c for is_in_life in /home/charla_n/projects/zappy/server/src
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Thu May 16 11:00:05 2013 nicolas charlas
** Last update Wed Jul 10 18:55:55 2013 nicolas charlas
*/

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "server.h"

int			event_player_die(t_srv *srv, t_client *client)
{
  t_graphic		g;

  g.graphic = srv->views;
  g.length_graphic = -1;
  g.players = client;
  return (pdi(srv, &g, NULL, NULL));
}

static int		egg_or_client(t_srv *srv, t_client **client)
{
  if ((*client)->type == FD_CLIENT)
    {
      if (event_player_die(srv, *client) == FAILURE)
	return (FAILURE);
      printf("\033[1mClient %d die !\033[0m\n", (*client)->fd);
      (*client)->team->nb_client++;
      (*client)->team = NULL;
      if ((*client)->incant)
	{
	  free((*client)->incant);
	  (*client)->incant = NULL;
	}
      if (write((*client)->fd, MESSAGE_DIE, strlen(MESSAGE_DIE)) <= 0)
	return (FAILURE);
      if (write((*client)->fd, DELIM, strlen(DELIM)) <= 0)
	return (FAILURE);
    }
  else if ((*client)->type == FD_EGG)
    {
      printf("\033[1;33mEgg %d is died\033[0m\n", (*client)->id);
      if (event_egg_died(srv, *client) == FAILURE)
	return (FAILURE);
      delete_client(&srv->eggs, client);
    }
  return (SUCCESS);
}

int			is_in_life(t_client **client, t_srv *srv)
{
  struct timeval	t;
  double		diff;

  if (((*client)->type == FD_CLIENT && (*client)->team) ||
      ((*client)->type == FD_EGG && (*client)->action.has_task == -1))
    {
      gettimeofday(&t, NULL);
      diff = (*client)->ttl.tv_sec - t.tv_sec
	+ (double)(*client)->ttl.tv_usec / 1000000.
	- (double)t.tv_usec / 1000000.;
      if (diff <= 0.)
	{
	  if (egg_or_client(srv, client) == FAILURE)
	    return (FAILURE);
	  return (0);
	}
    }
  else if (!(*client)->team && (*client)->type == FD_CLIENT)
    {
      gettimeofday(&(*client)->ttl, NULL);
      (*client)->ttl.tv_sec += DEFAULT_LIFE * 126 * 1 / srv->args.wait_time;
    }
  return (1);
}
