/*
** sbp.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Thu Jun 20 16:01:22 2013 nicolas charlas
** Last update Wed Jul  3 21:27:23 2013 nicolas charlas
*/

#include "server.h"

int	sbp(t_client *c)
{
  c->action.must_write++;
  if (write_circ(&c->buff_circ_w, "sbp"DELIM) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}
