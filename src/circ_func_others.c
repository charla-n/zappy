/*
** circ_func_others.c for zapy in /home/charla_n//projects/zappy/server
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Tue Jun  4 21:39:36 2013 nicolas charlas
** Last update Tue Jun 11 15:28:36 2013 arthur jansen
*/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "server.h"

int	initialize_circ(t_circ *circ)
{
  circ->size = BUFFER_SIZE;
  circ->start = 0;
  circ->end = 0;
  if ((circ->tab = malloc(sizeof(char) * BUFFER_SIZE)) == NULL)
    return (FAILURE);
  return (SUCCESS);
}

char	*read_circ(t_circ *circ, int speed)
{
  char	*str;
  int	i;

  if ((str = malloc(sizeof(char *) * (circ->size + 1))) == NULL)
    return (NULL);
  i = 0;
  bzero(str, circ->size + 1);
  while (circ->end != circ->start)
    {
      str[i] = circ->tab[circ->start];
      if (!speed && !strncmp(circ->tab + circ->start, DELIM, strlen(DELIM)))
	{
	  circ->start = (circ->start + 1) % circ->size;
	  return (str);
	}
      circ->start = (circ->start + 1) % circ->size;
      i++;
    }
  return (str);
}
