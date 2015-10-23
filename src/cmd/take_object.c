/*
** take_object.c for take_object in /home/charla_n/projects/zappy/server/src
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Fri May 17 13:31:09 2013 nicolas charlas
** Last update Fri Jul 12 15:12:55 2013 nicolas charlas
*/

#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "server.h"

static int	to_inventory(t_srv *srv, t_object *o, t_client *client)
{
  t_graphic	g;
  char		buff[11];

  if (o->type != FOOD)
    client->inventory[o->type]++;
  else
    client->ttl.tv_sec += 126 * 1 / srv->args.wait_time;
  g.graphic = srv->views;
  g.length_graphic = -1;
  g.players = client;
  if (pgt(srv, &g, (char *)&o->type, NULL) == FAILURE)
    return (FAILURE);
  g.length_graphic = -1;
  bzero(buff, 11);
  sprintf(buff, "%d", client->fd);
  return (pin(srv, &g, buff, NULL));
}

static int	verif_object(t_srv *srv, t_client *client, t_object *tmp,
			     char *cmd1)
{
  t_graphic	g;
  char		buff[11];
  char		buff2[11];

  bzero(buff, 11);
  bzero(buff2, 11);
  if (!strcmp(tmp->type_str, cmd1))
    {
      if (to_inventory(srv, tmp, client) == FAILURE)
	return (-2);
      delete_object(&srv->begin[client->position.x
				+ (client->position.y * srv->args.map_x)],
		    &tmp);
      sprintf(buff, "%d", client->position.x);
      sprintf(buff2, "%d", client->position.y);
      g.graphic = srv->views;
      g.length_graphic = -1;
      if (bct(srv, &g, buff, buff2) == FAILURE)
	return (-2);
      if (write_circ(&client->buff_circ_w, "ok"DELIM) == FAILURE)
	return (-2);
      init_time_task(srv, client, 7);
      return (SUCCESS);
    }
  return (FAILURE);
}

int		take_object(t_srv *srv, void *ptr, char *cmd1,
			    __attribute__((unused))char *cmd2)
{
  t_client	*client;
  t_object	*tmp;
  int		ret;

  client = (t_client *)ptr;
  tmp = srv->begin[client->position.x
		   + (client->position.y * srv->args.map_x)];
  while (cmd1 && strcmp(cmd1, "egg") && tmp)
    {
      if ((ret = verif_object(srv, client, tmp, cmd1)) == SUCCESS)
	return (SUCCESS);
      if (ret == -2)
	return (FAILURE);
      tmp = tmp->next;
    }
  if (write_circ(&client->buff_circ_w, "ko"DELIM) == FAILURE)
    return (FAILURE);
  init_time_task(srv, client, 7);
  return (SUCCESS);
}
