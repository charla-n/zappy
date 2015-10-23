/*
** parse_option.c for parse_option in /home/charla_n/projects/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Thu May  9 15:23:46 2013 nicolas charlas
** Last update Mon Jul  8 18:29:47 2013 nicolas charlas
*/

#define _GNU_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

extern char*	optarg;
extern int	optind;

int		usage()
{
  dprintf(2, "usage: server -n name_teams ... [-pxyct]\n"
	  "\t-p port number\n"
	  "\t-x map width\n"
	  "\t-y map height\n"
	  "\t-c number of clients at the beginning of the game\n"
	  "\t-t delay for executing actions\n");
  return (FAILURE);
}

static int	is_double_name(t_team **t, char *name)
{
  t_team	*tmp;

  tmp = *t;
  while (tmp != NULL)
    {
      if (!strcmp(name, tmp->name))
	{
	  dprintf(2, "Team's name already in use\n");
	  return (FAILURE);
	}
      tmp = tmp->next;
    }
  return (SUCCESS);
}

static int	put_in_list_team_name(t_team **t, char *name)
{
  t_team	*elem;

  if ((elem = malloc(sizeof(t_team))) == NULL)
    return (FAILURE);
  if (is_double_name(t, name))
    return (FAILURE);
  if (strlen(name) > MAX_TM_SIZE || strchr(name, ' '))
    return (FAILURE);
  elem->name = strdup(name);
  elem->next = *t;
  *t = elem;
  return (SUCCESS);
}

static int	parse_team_names(int ac, char * const av[], t_srv *srv)
{
  optind--;
  while (optind < ac && *av[optind] != '-')
    {
      if (put_in_list_team_name(&srv->args.team, av[optind]) == FAILURE)
	return (FAILURE);
      optind++;
    }
  return (SUCCESS);
}

int		parse_option(int ac, char * const av[], t_srv *srv)
{
  int		c;

  while ((c = getopt(ac, av, "+p:x:y:n:c:t:")) != -1)
    {
      if (c == 'p')
	srv->args.port = atoi(optarg);
      else if (c == 'x')
	srv->args.map_x = atoi(optarg);
      else if (c == 'y')
	srv->args.map_y = atoi(optarg);
      else if (c == 'n')
	{
	  if (parse_team_names(ac, av, srv) == FAILURE)
	    return (FAILURE);
	}
      else if (c == 'c')
	srv->args.nb_client_start = atoi(optarg);
      else if (c == 't')
	srv->args.wait_time = atoi(optarg);
      else
	return (usage());
    }
  return (SUCCESS);
}
