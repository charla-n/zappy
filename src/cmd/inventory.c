/*
** inventory.c for inventory in /home/charla_n/projects/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Fri May 17 13:31:09 2013 nicolas charlas
** Last update Fri Jul 12 16:24:45 2013 caroline trompf
*/

#define _GNU_SOURCE
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include "server.h"

int			inventory(t_srv *srv, void *ptr,
				  __attribute__((unused))char *cmd1,
				  __attribute__((unused))char *cmd2)
{
  t_client		*client;
  char			*buffer;
  struct timeval	t;

  client = (t_client *)ptr;
  gettimeofday(&t, NULL);
  if (asprintf(&buffer,
	       "{nourriture %u, linemate %u, deraumere %u, sibur %u, "
	       "mendiane %u, phiras %u, thystame %u}",
	       (int)(client->ttl.tv_sec - t.tv_sec),
	       client->inventory[LINEMATE],
	       client->inventory[DERAUMERE], client->inventory[SIBUR],
	       client->inventory[MENDIANE], client->inventory[PHIRAS],
	       client->inventory[THYSTAME]) == -1)
    return (FAILURE);
  if (write_circ(&client->buff_circ_w, buffer) == FAILURE)
    return (FAILURE);
  if (write_circ(&client->buff_circ_w, DELIM) == FAILURE)
    return (FAILURE);
  free(buffer);
  init_time_task(srv, client, 1);
  return (SUCCESS);
}
