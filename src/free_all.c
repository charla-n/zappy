/*
** free_all.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Thu Jun 20 10:13:58 2013 nicolas charlas
** Last update Wed Jul 10 17:33:45 2013 nicolas charlas
*/

#include <stdlib.h>
#include "server.h"

static void	free_map(t_object *tofree)
{
  t_object	*n;

  while (tofree)
    {
      n = tofree->next;
      free(tofree);
      tofree = n;
    }
}

static void	free_clients(t_client *c)
{
  t_client	*n;

  while (c)
    {
      n = c->next;
      if (c->type != FD_SERVER)
	{
	  if (c->incant)
	    free(c->incant);
	  free(c->buff_circ_w.tab);
	  free(c->buff_circ_r.tab);
	}
      free(c);
      c = n;
    }
}

static void	free_team(t_team *t)
{
  t_team	*n;

  while (t)
    {
      n = t->next;
      free(t->name);
      free(t);
      t = n;
    }
}

void	free_all(t_srv *srv)
{
  ui	i;

  i = 0;
  while (srv->begin && i < (srv->args.map_x * srv->args.map_y))
    {
      if (srv->begin[i])
	free_map(srv->begin[i]);
      i++;
    }
  free(srv->begin);
  free_clients(srv->eggs);
  free_clients(srv->views);
  free_clients(srv->clients);
  free_team(srv->args.team);
}
