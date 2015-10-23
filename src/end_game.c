/*
** end_game.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Fri Jun 21 14:40:57 2013 nicolas charlas
** Last update Thu Jul 11 18:48:10 2013 nicolas holder
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

static int	event_graphic_end(t_srv *srv, t_client *client)
{
  t_graphic	g;

  g.graphic = srv->views;
  g.length_graphic = -1;
  seg(srv, &g, client->team->name, NULL);
  return (SUCCESS);
}

int		end_game(t_srv *srv)
{
  int		end;
  t_client	*tmp;
  t_team	*team;

  team = srv->args.team;
  while (team)
    {
      end = 0;
      tmp = srv->clients;
      while (tmp)
	{
	  if (tmp->type == FD_CLIENT && tmp->team &&
	      !strcmp(tmp->team->name, team->name) && tmp->level == 8)
	    end++;
	  if (end == 6)
	    return (event_graphic_end(srv, tmp));
	  tmp = tmp->next;
	}
      team = team->next;
    }
  return (FAILURE);
}
