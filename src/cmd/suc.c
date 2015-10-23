/*
** suc.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Thu Jun 20 15:56:15 2013 nicolas charlas
** Last update Sat Jul 13 16:41:00 2013 arthur jansen
*/

#include "server.h"

int	suc(t_client *c)
{
  c->action.must_write++;
  if (write_circ(&c->buff_circ_w, "suc"DELIM) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}
