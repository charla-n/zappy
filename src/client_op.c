/*
** client_op.c for zappy in /home/charla_n/projects/zappy_git/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Tue Jun 11 13:24:10 2013 nicolas charlas
** Last update Fri Jul 12 12:45:18 2013 arthur jansen
*/

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include "server.h"

static int	disconnection(int fd)
{
  printf("\033[1mClient %d disconnected\033[0m\n", fd);
  return (DISCONNECTION);
}

int	client_read(t_srv *srv, t_client *client)
{
  int	ret;
  char	buffer[BUFFER_SIZE];

  (void)srv;
  bzero(buffer, BUFFER_SIZE);
  if (client->type == FD_GRAPHIC && nb_request(&client->buff_circ_w) > 0)
    return (SUCCESS);
  ret = read(client->fd, buffer, BUFFER_SIZE - 1);
  if (ret == -1 || !ret || !(ret = is_in_life(&client, srv)))
    return (disconnection(client->fd));
  if (ret == FAILURE)
    return (FAILURE);
  if (client->type == FD_CLIENT)
    printf("\t\033[1mreceive -> %s\033[0m", buffer);
  if ((nb_request(&client->buff_circ_r) + client->cmd_waiting) < MAX_REQUEST ||
      client->type == FD_GRAPHIC)
    {
      if (write_circ(&client->buff_circ_r, buffer) == FAILURE)
	return (FAILURE);
      return (call_parsing(srv, client));
    }
  else
    printf("\033[1;31mYou can't send more requests!\033[0m\n");
  return (SUCCESS);
}

int	client_write(t_srv *srv, t_client *client)
{
  char	*message;

  (void)srv;
  if (circ_end_mess(&client->buff_circ_w))
    {
      if (!(message = read_circ(&client->buff_circ_w, 0)))
	return (FAILURE);
      if (message[0])
	{
	  client->action.must_write--;
	  printf("\t\033[1mfor ia write -> %s\033[0m\n", message);
	  if (write(client->fd, message, strlen(message)) <= 0)
	    {
	      free(message);
	      return (DISCONNECTION);
	    }
	}
      free(message);
    }
  return (SUCCESS);
}

int	client_graphic_write(t_srv *srv, t_client *client)
{
  char	*message;
  int	ret;

  (void)srv;
  if (!(message = read_circ(&client->buff_circ_w, 1)))
    return (FAILURE);
  client->action.must_write = 0;
  if ((ret = write(client->fd, message, strlen(message))) <= 0)
    {
      free(message);
      return (DISCONNECTION);
    }
  if (ret < (int)strlen(message))
    if (write_circ(&client->buff_circ_w, message + ret) == FAILURE)
      return (FAILURE);
  free(message);
  return (SUCCESS);
}
