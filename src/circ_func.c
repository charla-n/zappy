/*
** circ_func.c for zappy in /home/charla_n/projects/zappy/server/src
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Wed May 15 21:02:22 2013 nicolas charlas
** Last update Wed Jul  3 17:22:58 2013 nicolas charlas
*/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "server.h"

static int	extends_circ(t_circ *circ)
{
  char		*tmp;
  int		i;

  if (!(tmp = read_circ(circ, 1)))
    return (FAILURE);
  if ((circ->tab = realloc(circ->tab, circ->size + STEP_REALLOC)) == NULL)
    return (FAILURE);
  circ->size += STEP_REALLOC;
  i = 0;
  while (tmp[i])
    {
      circ->tab[i] = tmp[i];
      i++;
    }
  free(tmp);
  circ->start = 0;
  circ->end = i;
  return (SUCCESS);
}

int	write_circ(t_circ *circ, char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      circ->tab[circ->end] = str[i];
      circ->end = (circ->end + 1) % circ->size;
      if (circ_full(circ) && circ->size < MAX_CIRC_SIZE)
      	{
      	  if (extends_circ(circ) == FAILURE)
      	    return (FAILURE);
      	}
      else if (circ_full(circ) && circ->size >= MAX_CIRC_SIZE)
      	circ->start = (circ->start + 1) % circ->size;
      i++;
    }
  return (SUCCESS);
}

char	circ_full(t_circ *circ)
{
  return (((circ->end + 1) % circ->size == circ->start) ? 1 : 0);
}

char	circ_end_mess(t_circ *circ)
{
  int	tmp;

  tmp = circ->start;
  while (circ->end != circ->start)
    {
      if (!strncmp(circ->tab + circ->start, DELIM, strlen(DELIM)))
	{
	  circ->start = tmp;
	  return (1);
	}
      circ->start = (circ->start + 1) % circ->size;
    }
  circ->start = tmp;
  return (0);
}

int	nb_request(t_circ *circ)
{
  int	tmp;
  int	count;

  count = 0;
  tmp = circ->start;
  while (circ->end != circ->start)
    {
      if (!strncmp(circ->tab + circ->start, DELIM, strlen(DELIM)))
	count++;
      circ->start = (circ->start + 1) % circ->size;
    }
  circ->start = tmp;
  return (count);
}
