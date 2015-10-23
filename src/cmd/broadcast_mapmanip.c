/*
** broadcast_mapmanip.c for zappy in /home/jansen_a/svn/zappy/server
** 
** Made by arthur jansen
** Login   <jansen_a@epitech.net>
** 
** Started on  Thu Jun 20 17:34:08 2013 arthur jansen
** Last update Fri Jul 12 16:18:19 2013 caroline trompf
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

void		free_broadcast_map(char **map)
{
  int		y;

  y = 0;
  while (map[y] != NULL)
    {
      free(map[y]);
      y++;
    }
  free(map);
  map = NULL;
}

char		**make_broadcast_map(t_srv *server)
{
  char		**ret;
  ui		y;
  ui		x;

  if ((ret = malloc(sizeof(char *) * ((server->args.map_y * 3) + 1))) == NULL)
    return (NULL);
  y = 0;
  while (y < (server->args.map_y * 3))
    {
      if ((ret[y] = malloc(sizeof(char) * ((server->args.map_x * 3) + 1)))
	  == NULL)
	return (NULL);
      x = 0;
      while (x < (server->args.map_x * 3))
	{
	  ret[y][x] = '0';
	  x++;
	}
      ret[y][x] = 0;
      y++;
    }
  ret[y] = NULL;
  return (ret);
}
