/*
** connect_nbr.c for connect_nbr in /home/charla_n/projects/zappy/server/src
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Fri May 17 13:31:09 2013 nicolas charlas
** Last update Fri Jul 12 15:06:08 2013 nicolas charlas
*/

#include <stdio.h>
#include <strings.h>
#include "server.h"

int		connect_nbr(t_srv *srv, void *ptr, char *cmd1, char *cmd2)
{
  t_client	*client;
  char		buff[11];

  client = (t_client *)ptr;
  (void)cmd1;
  (void)cmd2;
  bzero(buff, 11);
  sprintf(buff, "%d", client->team->nb_client);
  if (write_circ(&client->buff_circ_w, buff) == FAILURE)
    return (FAILURE);
  if (write_circ(&client->buff_circ_w, DELIM) == FAILURE)
    return (FAILURE);
  init_time_task(srv, client, 0);
  return (SUCCESS);
}
