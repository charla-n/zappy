/*
** drop_object.c for drop_object in /home/charla_n/projects/zappy/server/src
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Fri May 17 13:31:09 2013 nicolas charlas
** Last update Fri Jul 12 15:06:35 2013 nicolas charlas
*/

#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

static t_corresp_obj	g_obj[] =
  {
    {LINEMATE, "linemate"},
    {DERAUMERE, "deraumere"},
    {SIBUR, "sibur"},
    {MENDIANE, "mendiane"},
    {PHIRAS, "phiras"},
    {THYSTAME, "thystame"},
    {FOOD, "food"},
    {0, NULL}
  };

static int		fail_drop(t_client *client, t_srv *srv)
{
  if (write_circ(&client->buff_circ_w, "ko"DELIM) == FAILURE)
    return (FAILURE);
  init_time_task(srv, client, 7);
  return (SUCCESS);
}

static void		object_init_graphic(t_graphic *g, t_srv *srv,
					    t_client *client)
{
  g->graphic = srv->views;
  g->length_graphic = -1;
  g->players = client;
}

static int		object_exists(t_srv *srv, t_client *client,
				      t_corresp_obj o)
{
  char			buff[11];
  char			buff2[11];
  t_graphic		g;

  if (client->inventory[o.type] <= 0)
    return (fail_drop(client, srv));
  client->inventory[o.type]--;
  if (write_circ(&client->buff_circ_w, "ok"DELIM) == FAILURE)
    return (FAILURE);
  init_time_task(srv, client, 7);
  object_init_graphic(&g, srv, client);
  if (pdr(srv, &g, (char *)&o.type, NULL) == FAILURE)
    return (FAILURE);
  bzero(buff, 11);
  sprintf(buff, "%d", client->fd);
  if (pin(srv, &g, buff, NULL) == FAILURE)
    return (FAILURE);
  bzero(buff2, 11);
  bzero(buff, 11);
  sprintf(buff, "%d", client->position.x);
  sprintf(buff2, "%d", client->position.y);
  if (push_object(srv, o.type, client->position.x,
		  client->position.y) == FAILURE)
    return (FAILURE);
  return (bct(srv, &g, buff, buff2));
}

int		drop_object(t_srv *srv, void *ptr, char *cmd1,
			    __attribute__((unused))char *cmd2)
{
  int		i;
  t_client	*client;

  client = (t_client *)ptr;
  i = 0;
  if (!cmd1)
    return (fail_drop(client, srv));
  if (count_object(srv, client->position.x, client->position.y) ==
      FAILURE)
    return (fail_drop(client, srv));
  while (g_obj[i].name)
    {
      if (!strcmp(cmd1, g_obj[i].name))
	return (object_exists(srv, client, g_obj[i]));
      i++;
    }
  return (fail_drop(client, srv));
}
