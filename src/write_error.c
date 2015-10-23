/*
** write_error.c for zappy in /home/charla_n/projects/zappy/server/src
** 
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
** 
** Started on  Thu May  9 17:38:08 2013 nicolas charlas
** Last update Thu May  9 17:40:02 2013 nicolas charlas
*/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "server.h"

int	write_error(char *str, int fd)
{
  perror(str);
  close(fd);
  return (FAILURE);
}
