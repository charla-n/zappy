/*
** move_a_client.c for zappy in /home/jansen_a/svn/zappy/server
** 
** Made by arthur jansen
** Login   <jansen_a@epitech.net>
** 
** Started on  Wed Jun 26 17:15:17 2013 arthur jansen
** Last update Fri Jul 12 12:57:12 2013 arthur jansen
*/

#include <stdio.h>
#include "server.h"

void		move_client_to_north(t_client *client, t_srv *server)
{
  if (client->position.y == 0)
    client->position.y = (int)server->args.map_y - 1;
  else
    client->position.y -= 1;
}

void		move_client_to_south(t_client *client, t_srv *server)
{
  if (client->position.y == (int)server->args.map_y - 1)
    client->position.y = 0;
  else
    client->position.y += 1;
}

void		move_client_to_east(t_client *client, t_srv *server)
{
  if (client->position.x == (int)server->args.map_x - 1)
    client->position.x = 0;
  else
    client->position.x += 1;
}

void		move_client_to_west(t_client *client, t_srv *server)
{
  if (client->position.x == 0)
    client->position.x = server->args.map_x - 1;
  else
    client->position.x -= 1;
}
