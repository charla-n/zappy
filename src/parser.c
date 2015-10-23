/*
** parser.c for zappy in /home/charla_n/projects/zappy/server/src
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Fri May 17 13:09:01 2013 nicolas charlas
** Last update Fri Jul  5 14:29:41 2013 nicolas charlas
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

static t_parse	g_parser[] =
  {
    {"avance", &forward},
    {"droite", &right},
    {"gauche", &left},
    {"voir", &view},
    {"inventaire", &inventory},
    {"prend", &take_object},
    {"pose", &drop_object},
    {"expulse", &expulse},
    {"broadcast", &broadcast},
    {"incantation", &incantation},
    {"fork", &fork_player},
    {"connect_nbr", &connect_nbr},
    {NULL, NULL}
  };

static int	parser_engage(t_srv *srv, t_client *client, char *cmd)
{
  if (client->step_engage < 2)
    {
      if (!cmd)
	return (SUCCESS);
      return (engage_conversation(srv, client, cmd));
    }
  return (SUCCESS);
}

int		parser(t_srv *srv, t_client *client, char *cmd)
{
  char		*command;
  char		*arg1;
  char		*arg2;
  int		i;

  if ((i = parser_engage(srv, client, cmd)) == DISCONNECTION || i == FAILURE)
    return (i);
  if ((command = strtok(cmd, " ")))
    {
      if (!strcmp(cmd, "broadcast"))
	arg1 = strtok(NULL, "\0");
      else
	arg1 = strtok(NULL, " ");
      arg2 = strtok(NULL, "\0");
      i = 0;
      while (g_parser[i].name)
	{
	  if (!strcmp(command, g_parser[i].name))
	    return (g_parser[i].exec(srv, client, arg1, arg2));
	  i++;
	}
      client->step_engage++;
    }
  client->cmd_waiting--;
  return (SUCCESS);
}
