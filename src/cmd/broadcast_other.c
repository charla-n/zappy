/*
** broadcast_other.c for zappy in /home/jansen_a/svn/zappy/server/src/cmd
** 
** Made by arthur jansen
** Login   <jansen_a@epitech.net>
** 
** Started on  Mon Jul  1 14:38:34 2013 arthur jansen
** Last update Thu Jul 11 15:06:45 2013 arthur jansen
*/

#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "server.h"

static int		number_per_client_direction(t_client *tmpclient,
						    int i)
{
  if (i == 9)
    i = 1;
  else if (i == 0)
    i = 8;
  if (tmpclient->position.direction == NORTH)
    {
      i = i - 2;
      if (i <= 0)
	i = 8 + i;
    }
  else if (tmpclient->position.direction == SOUTH)
    {
      i = i + 2;
      if (i > 8)
	i = 0 - (8 - i);
    }
  else if (tmpclient->position.direction == WEST)
    {
      i = i - 4;
      if (i <= 0)
	i = 8 + i;
    }
  return (i);
}

static int		angle_to_number(double search_angle, t_client *client)
{
  double		angle[10];
  int			i;

  angle[0] = 0.0;
  angle[1] = 0.0;
  angle[2] = 45.0;
  angle[3] = 90.0;
  angle[4] = 135.0;
  angle[5] = 180.0;
  angle[6] = 225.0;
  angle[7] = 270.0;
  angle[8] = 315.0;
  angle[9] = 380.0;
  i = 0;
  while (i <= 8 && search_angle >= angle[i])
    i++;
  i--;
  if (search_angle == 45.0 || search_angle == 135.0
      || search_angle == 225.0 || search_angle == 315.0)
    return (number_per_client_direction(client, i));
  if ((i == 2 || i == 4 || i == 6 || i == 8) && search_angle > angle[i])
    i++;
  else if ((i == 2 || i == 4 || i == 6 || i == 8) && search_angle < angle[i])
    i--;
  return (number_per_client_direction(client, i));
}

static void		make_normal_vector(t_advvector *normal,
					   t_advvector *clienttotmp)
{
  normal->ax = clienttotmp->bx;
  normal->ay = clienttotmp->by;
  normal->bx = clienttotmp->bx + 1;
  normal->by = clienttotmp->by;
  normal->ab.x = (normal->bx - normal->ax);
  normal->ab.y = (normal->by - normal->ay);
  normal->ab.norme = 1;
}

static int		make_broadcast_angle(t_advvector *clienttotmp,
					     t_client *tmpclient)
{
  t_advvector		tmptoclient;
  t_advvector		normal;

  make_normal_vector(&normal, clienttotmp);
  tmptoclient.ay = clienttotmp->by;
  tmptoclient.ax = clienttotmp->bx;
  tmptoclient.ay = clienttotmp->by;
  tmptoclient.bx = clienttotmp->ax;
  tmptoclient.by = clienttotmp->ay;
  tmptoclient.ab.x = (tmptoclient.bx - tmptoclient.ax);
  tmptoclient.ab.y = (tmptoclient.by - tmptoclient.ay);
  tmptoclient.ab.norme = sqrt(pow(tmptoclient.ab.x, 2)
			      + pow(tmptoclient.ab.y, 2));
  tmptoclient.ab.angle = acos(((double)normal.ab.x * (double)tmptoclient.ab.x
			       + (double)normal.ab.y *
			       (double)tmptoclient.ab.y)
			      / ((double)normal.ab.norme *
				 (double)tmptoclient.ab.norme));
  tmptoclient.ab.angle *= (180.0 / M_PI);
  if (tmptoclient.ay < tmptoclient.by && tmptoclient.ab.angle < 180.0)
    tmptoclient.ab.angle = 360 - tmptoclient.ab.angle;
  return (angle_to_number(tmptoclient.ab.angle, tmpclient));
}

int			search_bro_direction(t_client *clientondemand,
					     t_client *tmpclient,
					     t_srv *server)
{
  t_listadvvector	*vectors;
  t_advvector		*clienttotmp;
  char			**map;
  int			finaldirection;

  vectors = NULL;
  if ((map = make_broadcast_map(server)) == NULL)
    return (FAILURE);
  if ((vectors = save_vectors(vectors, server, clientondemand, tmpclient, map))
      == NULL)
    return (FAILURE);
  clienttotmp = calcul_smallest_vector(vectors);
  finaldirection = make_broadcast_angle(clienttotmp, tmpclient);
  free_broadcast_vectorlist(vectors);
  free_broadcast_map(map);
  return (finaldirection);
}
