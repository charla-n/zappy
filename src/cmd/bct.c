/*
** bct.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Tue Jun 11 20:28:13 2013 nicolas charlas
** Last update Wed Jul  3 19:13:27 2013 nicolas charlas
*/

#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

static int	bct_write_result(t_graphic *g, int tab[7], int x, int y)
{
  t_client	*tmp;
  char		buff[25];

  tmp = g->graphic;
  bzero(buff, 25);
  sprintf(buff, "%d %d %d %d %d %d %d %d %d", x, y, tab[0], tab[1], tab[2],
	  tab[3], tab[4], tab[5], tab[6]);
  while (tmp && g->length_graphic)
    {
      if (tmp->type == FD_GRAPHIC)
	{
	  if (write_circ(&tmp->buff_circ_w, "bct ") == FAILURE ||
	      write_circ(&tmp->buff_circ_w, buff) == FAILURE ||
	      write_circ(&tmp->buff_circ_w, DELIM) == FAILURE)
	    return (FAILURE);
	  tmp->action.must_write++;
	}
      tmp = tmp->next;
      g->length_graphic--;
    }
  return (SUCCESS);
}

int		bct(t_srv *srv, void *ptr, char *cmd1, char *cmd2)
{
  t_graphic	*g;
  int		tab[7];
  int		x_asked;
  int		y_asked;
  t_object	*tmp;

  g = (t_graphic *)ptr;
  if (!cmd1 || !cmd2)
    return (sbp(g->graphic));
  if ((x_asked = atoi(cmd1)) >= (int)srv->args.map_x)
    return (SUCCESS);
  if ((y_asked = atoi(cmd2)) >= (int)srv->args.map_y)
    return (SUCCESS);
  tmp = srv->begin[x_asked + (y_asked * srv->args.map_x)];
  memset(tab, 0, sizeof(int) * 7);
  while (tmp)
    {
      tab[tmp->type]++;
      tmp = tmp->next;
    }
  return (bct_write_result(g, tab, x_asked, y_asked));
}
