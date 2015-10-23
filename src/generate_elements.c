/*
** generate_elements.c for generate_elements in /home/charla_n/projects/zappy/server/src
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Fri May 17 20:47:31 2013 nicolas charlas
** Last update Tue Jul  2 09:48:03 2013 nicolas charlas
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "server.h"

static t_luck_generate	g_gen[] =
  {
    {FOOD, 1},
    {LINEMATE, 1},
    {DERAUMERE, 3},
    {SIBUR, 5},
    {MENDIANE, 10},
    {PHIRAS, 15},
    {THYSTAME, 20}
  };

static int	random_generate_ressources(int x, int y, t_srv *srv)
{
  int		i;
  ui		generate;

  if (!(random() % 2))
    {
      if (push_object(srv, FOOD, x, y) == FAILURE)
	return (FAILURE);
    }
  else
    {
      generate = random() % 7;
      i = 0;
      while (g_gen[i].type != generate)
	i++;
      generate = random() % g_gen[i].luck + 1;
      if (generate == g_gen[i].luck &&
	  push_object(srv, g_gen[i].type, x, y) == FAILURE)
	return (FAILURE);
    }
  return (SUCCESS);
}

static int	generate(t_srv *srv)
{
  int		loop;
  int		x;
  int		y;
  int		failed;

  loop = (srv->args.map_x * srv->args.map_y) * 25 / 100;
  failed = 0;
  while (loop && failed != TRY_GENERATE)
    {
      x = random() % srv->args.map_x;
      y = random() % srv->args.map_y;
      if (count_object(srv, x, y) == SUCCESS)
	{
	  failed = 0;
	  if (random_generate_ressources(x, y, srv) == FAILURE)
	    return (FAILURE);
	  loop--;
	}
      else
	failed++;
    }
  return (SUCCESS);
}

time_t		generate_elements(t_srv *srv, int *res)
{
  static time_t	previous = 0;
  time_t	current;

  if (!previous)
    {
      previous = time(NULL);
      return (generate(srv));
    }
  current = time(NULL);
  if ((current - previous) >= TIME_GENERATE)
    {
      previous = current;
      if (generate(srv) == FAILURE)
	*res = -1;
      else
	return (TIME_GENERATE);
    }
  return (TIME_GENERATE - (current - previous));
}
