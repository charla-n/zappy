/*
** broadcast_vectormanip.c for zappy in /home/jansen_a/svn/zappy/server
** 
** Made by arthur jansen
** Login   <jansen_a@epitech.net>
** 
** Started on  Thu Jun 20 17:28:14 2013 arthur jansen
** Last update Fri Jul 12 16:19:37 2013 caroline trompf
*/

#define _XOPEN_SOURCE 600
#include <math.h>
#include <stdlib.h>
#include "server.h"

t_advvector		*calcul_smallest_vector(t_listadvvector *vectors)
{
  t_listadvvector	*tmp;
  double		smallest;

  tmp = vectors;
  smallest = tmp->vect.ab.norme;
  while (tmp != NULL)
    {
      if (tmp->vect.ab.norme < smallest)
	smallest = tmp->vect.ab.norme;
      tmp = tmp->next;
    }
  tmp = vectors;
  while (tmp->vect.ab.norme != smallest)
    tmp = tmp->next;
  return (&tmp->vect);
}

void			free_broadcast_vectorlist(t_listadvvector *vect)
{
  t_listadvvector	*tmp;
  t_listadvvector	*tofree;

  tmp = vect;
  while (tmp != NULL)
    {
      tofree = tmp;
      tmp = tmp->next;
      free(tofree);
    }
  vect = NULL;
}

t_listadvvector		*add_in_vectorlist(t_listadvvector *listvector,
					   t_advvector *vect)
{
  t_listadvvector	*tosave;
  t_listadvvector	*tmp;

  if ((tosave = malloc(sizeof(t_listadvvector))) == NULL)
    return (NULL);
  tosave->vect.ax = vect->ax;
  tosave->vect.ay = vect->ay;
  tosave->vect.bx = vect->bx;
  tosave->vect.by = vect->by;
  tosave->vect.ab.norme = vect->ab.norme;
  tosave->vect.ab.x = vect->ab.x;
  tosave->vect.ab.y = vect->ab.y;
  tosave->next = NULL;
  if (listvector == NULL)
    return (tosave);
  tmp = listvector;
  while (tmp && tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = tosave;
  return (listvector);
}

static t_advvector	*make_vector_client_to_tmp(t_srv *server,
						   t_client *clientondemand,
						   int xcase, int ycase)
{
  t_advvector		*thevector;

  if ((thevector = malloc(sizeof(t_advvector))) == NULL)
    return (NULL);
  thevector->ax = (server->args.map_x * 1)
    + clientondemand->position.x;
  thevector->ay = (server->args.map_y * 1)
    + clientondemand->position.y;
  thevector->bx = xcase;
  thevector->by = ycase;
  thevector->ab.x = (thevector->bx - thevector->ax);
  thevector->ab.y = (thevector->by - thevector->ay);
  thevector->ab.norme = sqrt(pow(thevector->ab.x, 2)
			     + pow(thevector->ab.y, 2));
  return (thevector);
}

t_listadvvector		*save_vectors(t_listadvvector *listvector,
				      t_srv *server, t_client *clientondemand,
				      t_client *tmpclient,
				      __attribute__((unused))char **map)
{
  t_advvector		*thevector;
  int			x;
  int			y;
  int			xcase;
  int			ycase;

  y = 0;
  while (y <= 2)
    {
      x = 0;
      while (x <= 2)
	{
	  xcase = (server->args.map_x * x) + tmpclient->position.x;
	  ycase = (server->args.map_y * y) + tmpclient->position.y;
	  if ((thevector = make_vector_client_to_tmp(server, clientondemand,
						     xcase, ycase)) == NULL)
	    return (NULL);
	  if ((listvector = add_in_vectorlist(listvector, thevector)) == NULL)
	    return (NULL);
	  free(thevector);
	  x++;
	}
      y++;
    }
  return (listvector);
}
