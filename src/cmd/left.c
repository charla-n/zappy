/*
** turn_left.c for turn_left in /home/jansen_a/svn/zappy/server/src/cmd
**
** Made by arthur jansen
** Login   <jansen_a@epitech.net>
**
** Started on  Fri May 17 14:15:39 2013 arthur jansen
** Last update Fri Jul 12 15:12:01 2013 nicolas charlas
*/

#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "server.h"

int		left(t_srv *server, void *ptr,
		     __attribute__((unused))char *arg,
		     __attribute__((unused))char *arg2)
{
  char		buff[11];
  t_client	*client;
  t_graphic	g;

  client = (t_client *)ptr;
  client->position.direction--;
  if (client->position.direction > WEST)
    client->position.direction = WEST;
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
