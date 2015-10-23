/*
** view_object_at.c for view_object_at.c in /home/jansen_a/svn/zappy/server/src/cmd
** 
** Made by arthur jansen
** Login   <jansen_a@epitech.net>
** 
** Started on  Thu Jul  4 18:40:57 2013 arthur jansen
** Last update Fri Jul 12 16:30:48 2013 caroline trompf
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "server.h"

int		object_at(int x, int y, char **answer, t_srv *srv)
{
  t_object	*tmp;
  char		*old;

  tmp = srv->begin[x + (srv->args.map_x * y)];
  while (tmp)
    {
      old = *answer;
      if (asprintf(answer, "%s%s ", *answer, tmp->type_str) == -1)
	return (FAILURE);
      free(old);
      tmp = tmp->next;
    }
  if (view_client(srv, x, y, answer) == FAILURE)
    return (FAILURE);
  old = *answer;
  if (asprintf(answer, "%s,", *answer) == -1)
    return (FAILURE);
  free(old);
  return (SUCCESS);
}
