/*
** main.c for server in /home/charla_n/projects/zappy/server
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Thu May  9 14:51:54 2013 nicolas charlas
** Last update Sat Jul  6 18:02:53 2013 nicolas charlas
*/

#define _GNU_SOURCE
#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "server.h"

t_srv		*g_srv;

static void	init_struct(t_srv *srv)
{
  srv->id_egg = 0;
  srv->clients = NULL;
  srv->begin = NULL;
  srv->views = NULL;
  srv->eggs = NULL;
  srv->args.team = NULL;
  srv->args.port = DEFAULT_PORT;
  srv->args.map_x = DEFAULT_MAPX;
  srv->args.map_y = DEFAULT_MAPY;
  srv->args.nb_client_start = DEFAULT_CSTA;
  srv->args.wait_time = DEFAULT_WAIT;
}

static int	init_nb_client_team(t_srv *srv)
{
  t_team	*tmp;

  if (!srv->args.team)
    {
      dprintf(2, "No team available\n");
      usage();
      return (FAILURE);
    }
  tmp = srv->args.team;
  while (tmp)
    {
      tmp->nb_client = srv->args.nb_client_start;
      tmp = tmp->next;
    }
  return (SUCCESS);
}

static void	catch_sig(int sig)
{
  (void)sig;
  free_all(g_srv);
  exit(0);
}

int		push_limits()
{
  struct rlimit	rlp;

  rlp.rlim_cur = MAX_FD;
  rlp.rlim_max = MAX_FD;
  if (setrlimit(RLIMIT_NOFILE, &rlp) == -1)
    return (write_error("push_limits() ", -1));
  getrlimit(RLIMIT_NOFILE, &rlp);
  return (SUCCESS);
}

int		main(int ac, char **av)
{
  t_srv		srv;

  g_srv = &srv;
  signal(SIGPIPE, SIG_IGN);
  signal(SIGINT, &catch_sig);
  init_struct(&srv);
  if (parse_option(ac, av, &srv) == FAILURE)
    return (FAILURE);
  if (init_nb_client_team(&srv) == FAILURE)
    return (FAILURE);
  if (srv.args.map_x > MAX_MAP_SIZE || srv.args.map_y > MAX_MAP_SIZE ||
      srv.args.map_x < MIN_MAP_SIZE || srv.args.map_y < MIN_MAP_SIZE)
    {
      dprintf(2, "Invalid map size %d %d, min %d max %d\n", srv.args.map_x,
	      srv.args.map_y, MIN_MAP_SIZE, MAX_MAP_SIZE);
      return (FAILURE);
    }
#ifdef EPOLL
  push_limits();
#endif
  return (processing(&srv));
}
