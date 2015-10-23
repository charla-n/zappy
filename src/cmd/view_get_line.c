/*
** view_get_line.c for zappy in /home/jansen_a/svn/zappy/server/src/cmd
** 
** Made by arthur jansen
** Login   <jansen_a@epitech.net>
** 
** Started on  Thu Jul  4 18:45:55 2013 arthur jansen
** Last update Fri Jul 12 16:30:35 2013 caroline trompf
*/

#include "server.h"

static t_vector	(*g_tab[4])(int, t_client *, t_srv *) =
{
  &get_begin_north,
  &get_begin_east,
  &get_begin_south,
  &get_begin_west
};

static int	case_check_eastwest(t_client *client, t_srv *srv,
				    t_tmpview *tmpview)
{
  if (client->position.direction == EAST)
    {
      if (object_at(tmpview->begin->x,
		    (tmpview->begin->y + tmpview->i - 1) % srv->args.map_y,
		    tmpview->answer, srv) == FAILURE)
	return (FAILURE);
    }
  if (client->position.direction == WEST)
    {
      if ((tmpview->begin->y - tmpview->i + 1) < 0)
	{
	  if (object_at(tmpview->begin->x,
			srv->args.map_y + tmpview->begin->y - tmpview->i + 1,
			tmpview->answer, srv) == FAILURE)
	    return (FAILURE);
	}
      else if (object_at(tmpview->begin->x, tmpview->begin->y - tmpview->i + 1,
			 tmpview->answer, srv) == FAILURE)
  	return (FAILURE);
    }
  return (SUCCESS);
}

static int	case_check_northsouth(t_client *client, t_srv *srv,
				      t_tmpview *tmpview)
{
  if (client->position.direction == NORTH)
    {
      if (object_at((tmpview->begin->x + tmpview->i - 1) % srv->args.map_x,
		    tmpview->begin->y, tmpview->answer, srv) == FAILURE)
	return (FAILURE);
    }
  if (client->position.direction == SOUTH)
    {
      if ((tmpview->begin->x - tmpview->i + 1) < 0)
	{
	  if (object_at(srv->args.map_x + tmpview->begin->x - tmpview->i + 1,
			tmpview->begin->y, tmpview->answer, srv) == FAILURE)
	    return (FAILURE);
	}
      else if (object_at(tmpview->begin->x - tmpview->i + 1,
			 tmpview->begin->y, tmpview->answer, srv) == FAILURE)
	return (FAILURE);
    }
  return (SUCCESS);
}

static int	case_by_case(t_client *client, char **answer,
			     int range, t_srv *srv)
{
  t_tmpview	tmpview;
  t_vector	begin;
  int		i;

  i = 1;
  begin = g_tab[client->position.direction](range / 2, client, srv);
  while (i < (range + 1))
    {
      tmpview.begin = &begin;
      tmpview.answer = answer;
      tmpview.i = i;
      if (case_check_northsouth(client, srv, &tmpview) == FAILURE)
	return (FAILURE);
      if (case_check_eastwest(client, srv, &tmpview) == FAILURE)
	return (FAILURE);
      i++;
    }
  return (SUCCESS);
}

int		view_get_line(t_client *client, char **answer, int range,
			      t_srv *srv)
{
  if (range == 1)
    {
      if (object_at(client->position.x, client->position.y, answer, srv)
	  == FAILURE)
	return (FAILURE);
    }
  else
    if (case_by_case(client, answer, range, srv) == FAILURE)
      return (FAILURE);
  return (SUCCESS);
}
