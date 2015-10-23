/*
** init_time_task.c for init_time_task in /home/charla_n/projects/zappy/server/src
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Wed May 22 22:14:05 2013 nicolas charlas
** Last update Fri Jul 12 14:20:39 2013 nicolas charlas
*/

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include "server.h"

void	init_time_task(t_srv *srv, t_client *client, int time_task)
{
  gettimeofday(&client->action.time_task, NULL);
  client->action.time_task.tv_sec += time_task / srv->args.wait_time;
  client->action.sec_task = time_task / srv->args.wait_time;
  client->action.duration = time_task;
  if ((int)(time_task /srv->args.wait_time) == 0)
    client->action.time_task.tv_usec += (1 / srv->args.wait_time) * 1000000;
  client->action.time_task.tv_usec %= 1000000;
  client->action.time_task.tv_sec +=
    client->action.time_task.tv_usec / 1000000;
  client->action.has_task = 1;
  printf("\033[1;32mAction will finish at %d %d and takes %d secs\033[0m\n",
	 (int)client->action.time_task.tv_sec,
	 (int)client->action.time_task.tv_usec,
	 time_task / srv->args.wait_time);
}
