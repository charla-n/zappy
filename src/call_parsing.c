/*
** call_parsing.c for call_parsing in /home/charla_n/projects/zappy/server/src
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Wed May 22 17:40:05 2013 nicolas charlas
** Last update Fri Jul 12 12:54:58 2013 arthur jansen
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

static int	parsing_free_cmd(char *cmd, t_srv *srv, t_client *client)
{
  int		ret;

  ret = parser(srv, client, cmd);
  if (ret == FAILURE)
    {
      free(cmd);
      return (FAILURE);
    }
  else if (ret == DISCONNECTION)
    {
      free(cmd);
      return (DISCONNECTION);
    }
  free(cmd);
  return (SUCCESS);
}

static int	graphic_parsing(t_srv *srv, t_client *client, char *cmd)
{
  t_graphic	g;
  int		ret;

  g.graphic = client;
  g.length_graphic = 1;
  g.players = NULL;
  if ((ret = graphic_clients_cmd(srv, cmd, &g)) == DISCONNECTION)
    {
      free(cmd);
      return (DISCONNECTION);
    }
  if (ret == FAILURE)
    {
      free(cmd);
      return (DISCONNECTION);
    }
  free(cmd);
  return (SUCCESS);
}

int		call_parsing(t_srv *srv, t_client *client)
{
  char		*cmd;
  int		ret;

  if (circ_end_mess(&client->buff_circ_r) &&
      client->action.has_task == -1)
    {
      client->cmd_waiting++;
      if (!(cmd = read_circ(&client->buff_circ_r, 0)))
	return (FAILURE);
      cmd[strlen(cmd) - 1] = 0;
      if (client->type == FD_CLIENT)
	printf("\033[1m\t\tparsing -> %s\033[0m\n\n", cmd);
      if (client->type == FD_GRAPHIC)
	ret = graphic_parsing(srv, client, cmd);
      else
	ret = parsing_free_cmd(cmd, srv, client);
      if (ret == FAILURE || ret == DISCONNECTION)
	return (ret);
      if (client->type == FD_GRAPHIC)
	return (call_parsing(srv, client));
    }
  return (SUCCESS);
}
