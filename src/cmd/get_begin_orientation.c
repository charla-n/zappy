/*
** get_begin_orientation.c for zappy in /home/charla_n/projects/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Mon Jul  1 23:04:50 2013 nicolas charlas
** Last update Fri Jul 12 16:23:05 2013 caroline trompf
*/

#include "server.h"

t_vector	get_begin_north(int range, t_client *client, t_srv *srv)
{
  int		tmp;
  t_vector	ret;

  tmp = range;
  ret.x = client->position.x;
  ret.y = client->position.y;
  while (range)
    {
      if (ret.x == 0)
	ret.x = srv->args.map_x - 1;
      else
	ret.x--;
      range--;
    }
  while (tmp)
    {
      if (ret.y == 0)
	ret.y = srv->args.map_y - 1;
      else
	ret.y--;
      tmp--;
    }
  return (ret);
}

t_vector	get_begin_west(int range, t_client *client, t_srv *srv)
{
  int		tmp;
  t_vector	ret;

  tmp = range;
  ret.x = client->position.x;
  ret.y = client->position.y;
  while (range)
    {
      if (ret.x == 0)
	ret.x = srv->args.map_x - 1;
      else
	ret.x--;
      range--;
    }
  while (tmp)
    {
      if (ret.y == (int)srv->args.map_y - 1)
	ret.y = 0;
      else
	ret.y++;
      tmp--;
    }
  return (ret);
}

t_vector	get_begin_east(int range, t_client *client, t_srv *srv)
{
  int		tmp;
  t_vector	ret;

  tmp = range;
  ret.x = client->position.x;
  ret.y = client->position.y;
  while (range)
    {
      if (ret.x == (int)srv->args.map_x - 1)
	ret.x = 0;
      else
	ret.x++;
      range--;
    }
  while (tmp)
    {
      if (ret.y == 0)
	ret.y = srv->args.map_y - 1;
      else
	ret.y--;
      tmp--;
    }
  return (ret);
}

t_vector	get_begin_south(int range, t_client *client, t_srv *srv)
{
  int		tmp;
  t_vector	ret;

  tmp = range;
  ret.x = client->position.x;
  ret.y = client->position.y;
  while (range)
    {
      if (ret.x == (int)srv->args.map_x - 1)
	ret.x = 0;
      else
	ret.x++;
      range--;
    }
  while (tmp)
    {
      if (ret.y == (int)srv->args.map_y - 1)
	ret.y = 0;
      else
	ret.y++;
      tmp--;
    }
  return (ret);
}
