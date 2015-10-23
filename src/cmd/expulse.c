/*
** expulse.c for expulse in /home/charla_n/projects/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Fri May 17 13:31:09 2013 nicolas charlas
** Last update Sat Jul 13 16:16:54 2013 arthur jansen
*/

#define _GNU_SOURCE
#include <strings.h>
#include <stdio.h>
#include "server.h"

static void	init_ptr_fct(int (*exp_to_client[4])(t_client *),
			     void (*expulse_move[4])(t_client *, t_srv *))
{
  expulse_move[NORTH] = &move_client_to_north;
  expulse_move[EAST] = &move_client_to_east;
  expulse_move[SOUTH] = &move_client_to_south;
  expulse_move[WEST] = &move_client_to_west;
  exp_to_client[NORTH] = &exp_client_to_north;
  exp_to_client[EAST] = &exp_client_to_east;
  exp_to_client[SOUTH] = &exp_client_to_south;
  exp_to_client[WEST] = &exp_client_to_west;
}

static int	search_client_to_expulse(t_srv *srv, t_client *client,
					 int (*exp_to_client[4])(t_client *),
					 void (*expulse_move[4])(t_client *,
								 t_srv *))
{
  t_client	*tmp;

  tmp = srv->clients;
  while (tmp != NULL)
    {
      if (tmp->type == FD_CLIENT
	  && tmp->fd != client->fd
	  && tmp->position.x == client->position.x
	  && tmp->position.y == client->position.y)
	{
	  expulse_move[client->position.direction](tmp, srv);
	  if (exp_to_client[client->position.direction](tmp) == FAILURE)
	    return (FAILURE);
	  if (event_players_expulsed(srv, tmp) == FAILURE)
	    return (FAILURE);
	}
      tmp = tmp->next;
    }
  return (SUCCESS);
}

int		expulse(t_srv *srv, void *ptr,
			__attribute__((unused))char *cmd1,
			__attribute__((unused))char *cmd2)
{
  t_client	*client;
  int		(*exp_to_client[4])(t_client *);
  void		(*expulse_move[4])(t_client *, t_srv *);

  client = (t_client *)ptr;
  init_ptr_fct(exp_to_client, expulse_move);
  if (event_expulse(srv, client) == FAILURE)
    return (FAILURE);
  if (search_client_to_expulse(srv, client, exp_to_client,
			       expulse_move) == FAILURE)
    return (FAILURE);
  if (write_circ(&client->buff_circ_w, "ok"DELIM) == FAILURE)
    return (FAILURE);
  init_time_task(srv, client, 7);
  return (SUCCESS);
}
