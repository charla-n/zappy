/*
** incantation.c for incantation in /home/charla_n/projects/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Fri May 17 13:31:09 2013 nicolas charlas
** Last update Sat Jul 13 14:47:47 2013 nicolas charlas
*/

#define	_GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "server.h"

static t_incantation	g_inc[] =
  {
    {2, 1, {1, 0, 0, 0, 0, 0}},
    {3, 2, {1, 1, 1, 0, 0, 0}},
    {4, 2, {2, 0, 1, 0, 2, 0}},
    {5, 4, {1, 1, 2, 0, 1, 0}},
    {6, 4, {1, 2, 1, 3, 0, 0}},
    {7, 6, {1, 2, 3, 0, 1, 0}},
    {8, 6, {2, 2, 2, 2, 2, 1}}
  };

static int	player_at_pos(t_srv *srv, t_client *client, t_client ***oth)
{
  int		ret;
  t_client	*tmp;

  ret = 1;
  tmp = srv->clients;
  if ((*oth = malloc(sizeof(t_client *) *
		     (g_inc[client->level - 1].need_player + 2))) == NULL)
    return (FAILURE);
  (*oth)[0] = client;
  while (tmp && ret < g_inc[client->level - 1].need_player)
    {
      if (tmp != client &&
	  tmp->type == FD_CLIENT && tmp->position.x == client->position.x &&
	  tmp->position.y == client->position.y &&
	  tmp->level == client->level &&
	  ret < g_inc[client->level - 1].need_player)
	{
	  (*oth)[ret] = tmp;
	  ret++;
	}
      tmp = tmp->next;
    }
  (*oth)[ret] = NULL;
  return (ret);
}

int		ressources_at_pos(t_srv *srv, int i, t_client *client,
				  t_object ***oth)
{
  int		ret;
  t_object	*tmp;

  tmp = srv->begin[client->position.x
		   + (client->position.y * srv->args.map_x)];
  ret = 0;
  if (!*oth)
    if ((*oth = malloc(sizeof(t_object *) * 11)) == NULL)
      return (FAILURE);
  while (tmp && ret < g_inc[client->level - 1].nb_needed[i])
    {
      if ((i + 1) == (int)tmp->type && ret <
	  g_inc[client->level - 1].nb_needed[i])
	{
	  (*oth)[client->objects_position++] = tmp;
	  ret++;
	}
      tmp = tmp->next;
    }
  (*oth)[client->objects_position] = NULL;
  return (ret);
}

static int	check_ressources(t_srv *srv, t_client *client,
				 t_object ***o_oth,
				 t_client **oth)
{
  int		i;
  int		ret;

  i = 0;
  client->objects_position = 0;
  while (i < 6)
    {
      if ((ret = ressources_at_pos(srv, i, client,
				   o_oth)) != FAILURE && ret <
	  g_inc[client->level - 1].nb_needed[i])
	{
	  return (incantation_send_msg(srv, client, *o_oth, oth));
	}
      if (ret == FAILURE)
	return (-2);
      i++;
    }
  return (FAILURE);
}

int		incantation(t_srv *srv, void *ptr,
			    __attribute__((unused))char *cmd1,
			    __attribute__((unused))char *cmd2)
{
  t_client	*client;
  t_client	**oth;
  t_object	**o_oth;
  int		ret;

  client = (t_client *)ptr;
  oth = NULL;
  o_oth = NULL;
  client->result = 0;
  if ((ret = player_at_pos(srv, client, &oth)) != FAILURE && ret <
      g_inc[client->level - 1].need_player)
    {
      return (incantation_send_msg(srv, client, o_oth, oth));
    }
  if (ret == FAILURE)
    return (FAILURE);
  if ((ret = check_ressources(srv, client, &o_oth, oth)) == SUCCESS ||
      ret == -2)
    return (ret == -2 ? FAILURE : SUCCESS);
  client->result = 1;
  if (client->level < 8)
    client->level++;
  return (incantation_send_msg(srv, client, o_oth, oth));
}
