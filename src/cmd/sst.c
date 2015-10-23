/*
** sst.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Thu Jun 20 16:10:23 2013 nicolas charlas
** Last update Thu Jul  4 13:46:22 2013 nicolas charlas
*/

#include <stdlib.h>
#include "server.h"

int		sst(t_srv *srv, void *ptr, char *cmd1,
		    __attribute__((unused))char *cmd2)
{
  t_graphic	*g;

  g = (t_graphic *)ptr;
  if (!cmd1)
    return (sbp(g->graphic));
  srv->args.wait_time = atoi(cmd1);
  if (sgt(srv, ptr, NULL, NULL) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}
