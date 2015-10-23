/*
** graphic_clients_cmd.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Wed Jun 12 15:00:33 2013 nicolas charlas
** Last update Fri Jun 21 12:38:47 2013 nicolas charlas
*/

#include <string.h>
#include "server.h"

static t_parse	g_parser[] =
  {
    {"msz", &msz},
    {"bct", &bct},
    {"mct", &mct},
    {"tna", &tna},
    {"ppo", &ppo},
    {"plv", &plv},
    {"pin", &pin},
    {"sgt", &sgt},
    {"sst", &sst},
    {NULL, NULL}
  };

int	graphic_clients_cmd(t_srv *srv, char *command, t_graphic *graph)
{
  int	i;
  char	*cmd1;
  char	*cmd2;
  char	*cmd;

  i = 0;
  if ((cmd = strtok(command, " ")))
    {
      cmd1 = strtok(NULL, " ");
      cmd2 = strtok(NULL, "\0");
      while (g_parser[i].name)
	{
	  if (!strcmp(g_parser[i].name, cmd))
	    return (g_parser[i].exec(srv, graph, cmd1, cmd2));
	  i++;
	}
    }
  return (suc(graph->graphic));
}
