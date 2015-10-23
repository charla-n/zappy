/*
** event_player_connection.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Fri Jun 21 12:46:26 2013 nicolas charlas
** Last update Thu Jul  4 13:30:46 2013 nicolas charlas
*/

#include <stdlib.h>
#include "server.h"

int		event_player_connection(t_srv *srv, t_client *client)
{
  t_graphic	g;

  g.graphic = srv->views;
  g.length_graphic = -1;
  g.players = client;
  g.length_players = 1;
  return (pnw(srv, &g, NULL, NULL));
}
