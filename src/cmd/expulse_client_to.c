/*
** expulse_client_to.c for zappy in /home/jansen_a/svn/zappy/server/src/cmd
** 
** Made by arthur jansen
** Login   <jansen_a@epitech.net>
** 
** Started on  Thu Jun 27 12:11:18 2013 arthur jansen
** Last update Sat Jul 13 14:47:15 2013 nicolas charlas
*/

#include <stdio.h>
#include "server.h"

int	exp_client_to_north(t_client *tmpclient)
{
  int	(*move_direction[4])(t_client *);

  move_direction[NORTH] = &exp_client_ahead;
  move_direction[EAST] = &exp_client_his_left;
  move_direction[SOUTH] = &exp_client_behind;
  move_direction[WEST] = &exp_client_his_right;
  if (move_direction[tmpclient->position.direction](tmpclient) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}

int	exp_client_to_east(t_client *tmpclient)
{
  int	(*move_direction[4])(t_client *);

  move_direction[NORTH] = &exp_client_his_right;
  move_direction[EAST] = &exp_client_ahead;
  move_direction[SOUTH] = &exp_client_his_left;
  move_direction[WEST] = &exp_client_behind;
  if (move_direction[tmpclient->position.direction](tmpclient) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}

int	exp_client_to_south(t_client *tmpclient)
{
  int	(*move_direction[4])(t_client *);

  move_direction[NORTH] = &exp_client_behind;
  move_direction[EAST] = &exp_client_his_right;
  move_direction[SOUTH] = &exp_client_ahead;
  move_direction[WEST] = &exp_client_his_left;
  if (move_direction[tmpclient->position.direction](tmpclient) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}

int	exp_client_to_west(t_client *tmpclient)
{
  int	(*move_direction[4])(t_client *);

  move_direction[NORTH] = &exp_client_his_left;
  move_direction[EAST] = &exp_client_behind;
  move_direction[SOUTH] = &exp_client_his_right;
  move_direction[WEST] = &exp_client_ahead;
  if (move_direction[tmpclient->position.direction](tmpclient) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}
