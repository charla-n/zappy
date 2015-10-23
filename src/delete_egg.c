/*
** delete_egg.c for zappy in /home/bender/projects/zappy/server
** 
** Made by nicolas charlas
** Login   <bender@epitech.net>
** 
** Started on  Thu Jul  4 15:55:16 2013 nicolas charlas
** Last update Thu Jul  4 16:10:50 2013 nicolas charlas
*/

#include "server.h"

int		delete_egg(t_object **object)
{
  t_object	*tmp;

  tmp = *object;
  while (tmp)
    {
      if (tmp->type == EGG)
	{
	  delete_object(object, &tmp);
	  return (SUCCESS);
	}
      tmp = tmp->next;
    }
  return (SUCCESS);
}
