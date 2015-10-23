/*
** processing.c for processing in /home/charla_n/projects/zappy/server/src
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Thu May  9 17:03:20 2013 nicolas charlas
** Last update Wed Jul 10 19:17:55 2013 nicolas charlas
*/

#define _GNU_SOURCE
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include "server.h"

void			calc_time(struct timeval *t, struct timeval td,
				  t_client *tmp)
{
  if ((tmp->type == FD_CLIENT || tmp->type == FD_EGG) && tmp->team &&
      ((tmp->action.has_task != -1 && tmp->action.sec_task < t->tv_sec) ||
       (int)((tmp->ttl.tv_sec - td.tv_sec) < t->tv_sec)))
    {
      t->tv_sec = tmp->action.time_task.tv_sec - td.tv_sec;
      if ((tmp->action.has_task == -1) ||
	  (int)(tmp->ttl.tv_sec - td.tv_sec) < t->tv_sec)
	t->tv_sec = tmp->ttl.tv_sec - td.tv_sec;
      if ((int)t->tv_sec < 0)
	t->tv_sec = 0;
    }
}

void			get_time(struct timeval *t, t_srv *srv)
{
  t_client		*tmp;
  struct timeval	td;

  tmp = srv->clients;
  t->tv_usec = 0;
  gettimeofday(&td, NULL);
  while (tmp)
    {
      calc_time(t, td, tmp);
      tmp = tmp->next;
    }
  tmp = srv->eggs;
  while (tmp)
    {
      calc_time(t, td, tmp);
      tmp = tmp->next;
    }
  tmp = srv->views;
  while (tmp)
    {
      if ((tmp->type == FD_GRAPHIC && nb_request(&tmp->buff_circ_r) > 0) ||
	  (tmp->type == FD_GRAPHIC && nb_request(&tmp->buff_circ_w) > 0))
	t->tv_sec = 0;
      tmp = tmp->next;
    }
}

int		do_manage(t_srv *srv)
{
  if (clients_still_alive(srv->clients, srv) == FAILURE)
    return (FAILURE);
  if (manage_task(srv, srv->clients) == FAILURE)
    return (FAILURE);
  if (manage_task(srv, srv->eggs) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}

#ifndef EPOLL
static int		loop(t_srv *srv)
{
  struct timeval	t;
  int			has_data_write;
  int			res;
  int			max;

  res = 0;
  while (res != -1)
    {
      max = 0;
      has_data_write = 0;
      initialize(srv, &max, &has_data_write, srv->clients);
      t.tv_sec = generate_elements(srv, &res);
      if (res == -1)
      	return (FAILURE);
      get_time(&t, srv);
      res = select(max + 1, &srv->read,
		   (has_data_write ? &srv->write : NULL), NULL, &t);
      if (is_flaged(srv, srv->clients) == FAILURE)
	return (FAILURE);
      if (end_game(srv) == SUCCESS)
	return (SUCCESS);
      if (do_manage(srv) == FAILURE)
	return (FAILURE);
    }
  return ((res == -1) ? FAILURE : SUCCESS);
}
#endif

int		processing(t_srv *srv)
{
  ui		i;

  srv->begin = malloc(sizeof(t_object*) * (srv->args.map_x * srv->args.map_y));
  if (!srv->begin)
    return (FAILURE);
  i = 0;
  while (i < srv->args.map_x * srv->args.map_y)
    {
      srv->begin[i] = NULL;
      i++;
    }
  srandom(time(NULL));
  if (connect_to(srv) == FAILURE)
    return (FAILURE);
  i = loop(srv);
  free_all(srv);
  return (i);
}
