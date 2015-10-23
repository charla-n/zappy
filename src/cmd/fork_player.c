/*
** fork_player.c for fork_player in /home/charla_n/projects/zappy/server/src
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Fri May 17 13:31:09 2013 nicolas charlas
** Last update Fri Jul 12 15:08:43 2013 nicolas charlas
*/

#define _BSD_SOURCE
#include <stdlib.h>
#include "server.h"

static int	set_n_param(t_client *n, t_client *client,
			    t_srv *srv)
{
  n->position.x = client->position.x;
  n->position.y = client->position.y;
  n->team = client->team;
  n->position.direction = random() % 4;
  n->fd = -1;
  n->by = client->fd;
  n->id = srv->id_egg++;
  if (write_circ(&client->buff_circ_w, "ok"DELIM) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}

static void	fork_init_graphic(t_graphic *g, t_srv *srv, t_client *client)
{
  g->graphic = srv->views;
  g->length_graphic = -1;
  g->length_players = -1;
  g->players = client;
}

int		fork_player(t_srv *srv, void *ptr,
			    __attribute__((unused))char *cmd1,
			    __attribute__((unused))char *cmd2)
{
  t_client	*client;
  t_client	*n;
  t_graphic	g;
  int		(*fct[2])(t_srv *, t_client *);

  client = (t_client *)ptr;
  client->team->nb_client++;
  if (push_object(srv, EGG, client->position.x, client->position.y) == FAILURE)
    return (FAILURE);
  init_time_task(srv, client, 42);
  fct[0] = &client_read;
  fct[1] = &client_write;
  if (!(n = put_in_list_client(-1, FD_EGG, &srv->eggs, fct)))
    return (FAILURE);
  if (init_client(n, srv) == NULL)
    return (FAILURE);
  if (set_n_param(n, client, srv) == FAILURE)
    return (FAILURE);
  init_time_task(srv, n, 600);
  fork_init_graphic(&g, srv, client);
  if (pfk(srv, &g, NULL, NULL) == FAILURE)
    return (FAILURE);
  g.length_players = 1;
  g.players = n;
  return (enw(srv, &g, NULL, NULL));
}
