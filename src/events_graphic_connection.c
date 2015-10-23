/*
** events_graphic_connection.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Fri Jun 14 13:08:01 2013 nicolas charlas
** Last update Thu Jul  4 12:58:38 2013 nicolas charlas
*/

#include <stdlib.h>
#include "server.h"

int		events_graphic_connection(t_srv *srv, t_client *client)
{
  t_graphic	g;

  g.graphic = client;
  g.length_graphic = 1;
  if (msz(srv, &g, NULL, NULL) == FAILURE)
    return (FAILURE);
  g.length_graphic = 1;
  if (sgt(srv, &g, NULL, NULL) == FAILURE)
    return (FAILURE);
  g.length_graphic = 1;
  if (mct(srv, &g, NULL, NULL) == FAILURE)
    return (FAILURE);
  g.length_graphic = 1;
  if (tna(srv, &g, NULL, NULL) == FAILURE)
    return (FAILURE);
  g.length_graphic = 1;
  g.players = srv->clients;
  g.length_players = -1;
  if (pnw(srv, &g, NULL, NULL) == FAILURE)
    return (FAILURE);
  g.players = srv->eggs;
  g.length_graphic = 1;
  g.length_players = -1;
  return (enw(srv, &g, NULL, NULL));
}
