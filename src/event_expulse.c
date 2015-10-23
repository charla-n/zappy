/*
** event_expulse.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Fri Jun 21 13:50:30 2013 nicolas charlas
** Last update Thu Jul  4 13:11:33 2013 nicolas charlas
*/

#define _BSD_SOURCE
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"

int		event_expulse(t_srv *srv, t_client *client)
{
  t_graphic	g;

  g.graphic = srv->views;
  g.length_graphic = -1;
  g.players = client;
  g.length_players = 1;
  return (pex(srv, &g, NULL, NULL));
}

int		event_players_expulsed(t_srv *srv, t_client *client)
{
  t_graphic	g;
  char		buff[11];

  bzero(buff, 11);
  g.graphic = srv->views;
  g.length_graphic = -1;
  sprintf(buff, "%d", client->fd);
  return (ppo(srv, &g, buff, NULL));
}
