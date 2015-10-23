/*
** view.c for view in /home/charla_n/projects/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Fri May 17 13:31:09 2013 nicolas charlas
** Last update Fri Jul 12 15:13:54 2013 nicolas charlas
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"

static int	get_content_from_pos(t_client *client, t_srv *srv,
				     char **answer, int range)
{
  int		i;

  i = -1;
  range = 1;
  while (i < (int)client->level)
    {
      if (view_get_line(client, answer, range, srv) == FAILURE)
	return (FAILURE);
      range += 2;
      i++;
    }
  return (SUCCESS);
}

int		view(t_srv *srv, void *ptr,
		     __attribute__((unused))char *cmd1,
		     __attribute__((unused))char *cmd2)
{
  char		*answer;
  char		*old;
  t_client	*client;

  client = (t_client *)ptr;
  if (asprintf(&answer, "{") == -1)
    return (FAILURE);
  if (get_content_from_pos(client, srv, &answer, 0) == FAILURE)
    return (FAILURE);
  answer[strrchr(answer, ',') - answer] = 0;
  old = answer;
  if (asprintf(&answer, "%s}", answer) == -1)
    return (FAILURE);
  free(old);
  if (write_circ(&client->buff_circ_w, answer) == FAILURE)
    return (FAILURE);
  if (write_circ(&client->buff_circ_w, DELIM) == FAILURE)
    return (FAILURE);
  free(answer);
  init_time_task(srv, client, 7);
  return (SUCCESS);
}
