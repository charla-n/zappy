/*
** expulse_direction.c for zappy in /home/jansen_a/svn/zappy/server
** 
** Made by arthur jansen
** Login   <jansen_a@epitech.net>
** 
** Started on  Tue Jun 11 14:58:38 2013 arthur jansen
** Last update Sat Jul 13 16:18:50 2013 arthur jansen
*/

#include <stdio.h>
#include "server.h"

int		exp_client_ahead(t_client *tmpclient)
{
  if (write_circ(&tmpclient->buff_circ_w, "deplacement: 5"DELIM) == FAILURE)
    return (FAILURE);
  tmpclient->action.must_write++;
  return (SUCCESS);
}

int		exp_client_his_left(t_client *tmpclient)
{
  if (write_circ(&tmpclient->buff_circ_w, "deplacement: 7"DELIM) == FAILURE)
    return (FAILURE);
  tmpclient->action.must_write++;
  return (SUCCESS);
}

int		exp_client_behind(t_client *tmpclient)
{
  if (write_circ(&tmpclient->buff_circ_w, "deplacement: 1"DELIM) == FAILURE)
    return (FAILURE);
  tmpclient->action.must_write++;
  return (SUCCESS);
}

int		exp_client_his_right(t_client *tmpclient)
{
  if (write_circ(&tmpclient->buff_circ_w, "deplacement: 3"DELIM) == FAILURE)
    return (FAILURE);
  tmpclient->action.must_write++;
  return (SUCCESS);
}
