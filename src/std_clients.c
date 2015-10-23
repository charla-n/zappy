/*
** std_clients.c for std_clients in /home/charla_n/projects/zappy/server/src
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Wed May 15 13:03:38 2013 nicolas charlas
** Last update Wed Jul 10 18:56:23 2013 nicolas charlas
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

static char	*g_object[] =
  {
    "nourriture",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
    "egg",
    NULL
  };

int		push_object(t_srv *srv, t_type type, int x, int y)
{
  t_object	*elem;

  if (count_object(srv, x, y) == SUCCESS)
    {
      if ((elem = malloc(sizeof(t_object))) == NULL)
	return (FAILURE);
      elem->position.x = x;
      elem->position.y = y;
      if (type <= 7)
	elem->type_str = g_object[type];
      elem->type = type;
      elem->next = srv->begin[x + (srv->args.map_x * y)];
      srv->begin[x + (srv->args.map_x * y)] = elem;
    }
  return (SUCCESS);
}

int		count_object(t_srv *srv, int x, int y)
{
  t_object	*tmp;
  int		count;

  count = 0;
  tmp = srv->begin[x + (srv->args.map_x * y)];
  while (tmp)
    {
      if (count == MAX_OBJ_CASE)
	return (FAILURE);
      count++;
      tmp = tmp->next;
    }
  if (count == MAX_OBJ_CASE)
    return (FAILURE);
  return (SUCCESS);
}

void		delete_object(t_object **objs, t_object **todelete)
{
  t_object	*tmp;
  t_object	*prev;
  t_object	*f;

  prev = NULL;
  tmp = *objs;
  while (tmp && !prev)
    {
      if (tmp->next == *todelete)
	prev = tmp;
      tmp = tmp->next;
    }
  if (!prev)
    {
      f = *todelete;
      *objs = (*objs)->next;
      free(f);
    }
  else
    {
      prev->next = (*todelete)->next;
      free(*todelete);
    }
}

static void	delete_ressource(t_client **todelete)
{
  if ((*todelete)->incant)
    {
      free((*todelete)->incant);
      (*todelete)->incant = NULL;
    }
  free((*todelete)->buff_circ_w.tab);
  free((*todelete)->buff_circ_r.tab);
  free(*todelete);
}

void		delete_client(t_client **clients, t_client **todelete)
{
  t_client	*tmp;
  t_client	*prev;

  prev = NULL;
  tmp = *clients;
  while (tmp && !prev)
    {
      if (tmp->next == *todelete)
	prev = tmp;
      tmp = tmp->next;
    }
  if (!prev)
    {
      *clients = (*clients)->next;
      delete_ressource(todelete);
      *todelete = *clients;
    }
  else
    {
      prev->next = (*todelete)->next;
      delete_ressource(todelete);
      *todelete = prev->next;
    }
}
