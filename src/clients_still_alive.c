/*
** clients_still_alive.c for zappy in /home/charla_n/projects/zappy/server/src
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Wed May 22 23:10:21 2013 nicolas charlas
** Last update Thu Jul  4 19:52:48 2013 arthur jansen
*/

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include "server.h"

static int	check_is_in_life(int ret, t_client *tmp, char *delete)
{
  if (ret == FAILURE)
    return (FAILURE);
  if (tmp && tmp->type == FD_CLIENT)
    {
      close(tmp->fd);
      tmp->type = FD_FREE;
    }
  else
    *delete = 1;
  return (SUCCESS);
}

int		clients_still_alive(t_client *clients, t_srv *srv)
{
  int		ret;
  t_client	*tmp;
  char		delete;

  tmp = clients;
  while (tmp)
    {
      delete = 0;
      if ((tmp->type == FD_CLIENT || tmp->type == FD_EGG) &&
	  !(ret = is_in_life(&tmp, srv)))
	if (check_is_in_life(ret, tmp, &delete) == FAILURE)
	  return (FAILURE);
      if (!delete)
	tmp = tmp->next;
    }
  if (clients != srv->eggs)
    return (clients_still_alive(srv->eggs, srv));
  return (SUCCESS);
}
