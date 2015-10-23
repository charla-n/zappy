/*
** pic.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Wed Jun 12 20:25:44 2013 nicolas charlas
** Last update Wed Jul 10 13:45:33 2013 nicolas charlas
*/

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "server.h"

static int	pic_send_to_client(t_graphic *g, char *buff)
{
  t_client	*tmp;

  tmp = g->graphic;
  while (tmp && g->length_graphic)
    {
      if (tmp->type == FD_GRAPHIC)
	{
	  tmp->action.must_write++;
	  if (write_circ(&tmp->buff_circ_w, "pic ") == FAILURE ||
	      write_circ(&tmp->buff_circ_w, buff) == FAILURE ||
	      write_circ(&tmp->buff_circ_w, DELIM) == FAILURE)
	    return (FAILURE);
	}
      tmp = tmp->next;
      g->length_graphic--;
    }
  return (SUCCESS);
}

int		pic(__attribute__((unused))t_srv *srv, void *ptr,
		    __attribute__((unused))char *cmd1,
		    __attribute__((unused))char *cmd2)
{
  char		nb[12];
  int		i;
  t_client	**tab;
  t_graphic	*g;
  char		buff[110];
  int		first;

  first = 0;
  bzero(buff, 110);
  g = (t_graphic *)ptr;
  tab = ((t_client **)(g->players));
  i = 0;
  bzero(nb, 11);
  sprintf(buff, "%d %d %d ", tab[0]->position.x, tab[0]->position.y,
	  tab[0]->level);
  while (tab && tab[i])
    {
      sprintf(nb, "%s%d", !first ? "" : " ", tab[i]->fd);
      first = 1;
      strcat(buff, nb);
      i++;
    }
  return (pic_send_to_client(g, buff));
}
