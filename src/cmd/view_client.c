/*
** view_client.c for zappy in /home/bender/projects/zappy/server
** 
** Made by nicolas charlas
** Login   <bender@epitech.net>
** 
** Started on  Thu Jul  4 17:41:44 2013 nicolas charlas
** Last update Thu Jul  4 17:47:05 2013 nicolas charlas
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "server.h"

int		view_client(t_srv *srv, int x, int y, char **answer)
{
  t_client	*tmp;
  char		*old;

  tmp = srv->clients;
  while (tmp)
    {
      if (tmp->type == FD_CLIENT && tmp->position.x == x &&
	  tmp->position.y == y)
	{
	  old = *answer;
	  if (asprintf(answer, "%s%s ", *answer, "joueur") == -1)
	    return (FAILURE);
	  free(old);
	}
      tmp = tmp->next;
    }
  return (SUCCESS);
}
