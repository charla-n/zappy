/*
** cmd_avance.c for cmd_avance in /home/jansen_a/svn/zappy/server/src/cmd
** 
** Made by arthur jansen
** Login   <jansen_a@epitech.net>
** 
** Started on  Fri May 17 13:11:29 2013 arthur jansen
** Last update Fri Jul 12 14:20:52 2013 nicolas charlas
*/

#define _BSD_SOURCE
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "server.h"

int		forward(t_srv *server, void *ptr,
			__attribute__((unused))char *arg,
			__attribute__((unused))char *arg2)
{
  char		buff[11];
  t_graphic	g;
  t_client	*client;
  void		(*fct[4])(t_client *, t_srv *);

  client = (t_client *)ptr;
  fct[0] = &move_client_to_north;
  fct[1] = &move_client_to_east;
  fct[2] = &move_client_to_south;
  fct[3] = &move_client_to_west;
  fct[client->position.direction](client, server);
  if (write_circ(&client->buff_circ_w, "ok"DELIM) == FAILURE)
    return (FAILURE);
  init_time_task(server, client, 7);
  g.graphic = server->views;
  g.length_graphic = -1;
  g.players = client;
  g.length_players = 1;
  bzero(buff, 11);
  sprintf(buff, "%d", client->fd);
  return (ppo(server, &g, buff, NULL));
}
