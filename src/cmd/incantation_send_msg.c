/*
** incantation_send_msg.c for zappy in /home/jansen_a/svn/zappy/server/src/cmd
** 
** Made by arthur jansen
** Login   <jansen_a@epitech.net>
** 
** Started on  Mon Jul  1 13:32:20 2013 arthur jansen
** Last update Fri Jul 12 16:24:24 2013 caroline trompf
*/

#include <strings.h>
#include <stdlib.h>
#include "server.h"

static int	event_incantation(t_srv *srv, t_client **oth)
{
  t_graphic	g;

  g.graphic = srv->views;
  g.length_graphic = -1;
  g.players = oth;
  return (pic(srv, &g, NULL, NULL));
}

static void	del_incantation_objects(t_object **o_oth, t_srv *srv)
{
  int		i;

  i = 0;
  while (o_oth && o_oth[i])
    {
      delete_object(&srv->begin[o_oth[i]->position.x
				+ (o_oth[i]->position.y *
				   srv->args.map_x)], &o_oth[i]);
      i++;
    }
}

static int	send_incantation_to_client(t_client *client, t_client **oth,
					   t_srv *srv)
{
  int		i;
  char		buff[2];

  bzero(buff, 2);
  buff[0] = client->level + '0';
  i = 0;
  while (oth && oth[i])
    {
      if (oth[i]->level != client->level)
	oth[i]->level = client->level;
      oth[i]->action.must_write++;
      if (write_circ(&oth[i]->buff_circ_w,
		     "elevation en cours"DELIM) == FAILURE
	  || write_circ(&oth[i]->buff_circ_w, "niveau actuel : ") == FAILURE
	  || write_circ(&oth[i]->buff_circ_w, buff) == FAILURE
	  || write_circ(&oth[i]->buff_circ_w, DELIM) == FAILURE)
	return (FAILURE);
      init_time_task(srv, oth[i], 300);
      i++;
    }
  return (SUCCESS);
}

int		incantation_send_msg(t_srv *srv, t_client *client,
				     t_object **o_oth, t_client **oth)
{
  if (send_incantation_to_client(client, oth, srv) == FAILURE)
    return (FAILURE);
  if (oth)
    if (event_incantation(srv, oth) == FAILURE)
      return (FAILURE);
  del_incantation_objects(o_oth, srv);
  if (o_oth)
    free(o_oth);
  client->incant = oth;
  return (SUCCESS);
}
