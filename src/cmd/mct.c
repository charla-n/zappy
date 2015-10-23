/*
** mct.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Tue Jun 11 21:06:47 2013 nicolas charlas
** Last update Thu Jul  4 13:04:22 2013 nicolas charlas
*/

#include <strings.h>
#include <stdio.h>
#include "server.h"

static int	mct_send_to_client(t_srv *srv, t_graphic *g, ui y,
				   int last, void *ptr)
{
  ui		x;
  char		buffx[4];
  char		buffy[4];

  bzero(buffx, 4);
  bzero(buffy, 4);
  x = 0;
  while (x < srv->args.map_x)
    {
      g->length_graphic = last;
      sprintf(buffx, "%d", x);
      sprintf(buffy, "%d", y);
      if (bct(srv, ptr, buffx, buffy) == FAILURE)
	return (FAILURE);
      x++;
    }
  return (SUCCESS);
}

int		mct(t_srv *srv, void *ptr, char *cmd1, char *cmd2)
{
  int		last;
  t_graphic	*g;
  ui		y;

  (void)cmd1;
  (void)cmd2;
  y = 0;
  g = (t_graphic *)ptr;
  last = g->length_graphic;
  while (y < srv->args.map_y)
    {
      if (mct_send_to_client(srv, g, y, last, ptr) == FAILURE)
	return (FAILURE);
      y++;
    }
  return (SUCCESS);
}
