/*
** event_egg.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Fri Jun 21 15:06:42 2013 nicolas charlas
** Last update Thu Jul  4 13:25:21 2013 nicolas charlas
*/

#include <stdlib.h>
#include "server.h"

int		event_egg(t_srv *srv, t_client *egg)
{
  t_graphic	g;

  g.graphic = srv->views;
  g.length_graphic = -1;
  g.players = egg;
  return (ebo(srv, &g, NULL, NULL));
}

int		event_egg_opened(t_srv *srv, t_client *egg)
{
  t_graphic	g;

  g.graphic = srv->views;
  g.length_graphic = -1;
  g.players = egg;
  return (eht(srv, &g, NULL, NULL));
}

int		event_egg_died(t_srv *srv, t_client *egg)
{
  t_graphic	g;

  g.graphic = srv->views;
  g.length_graphic = -1;
  g.players = egg;
  return (edi(srv, &g, NULL, NULL));
}
