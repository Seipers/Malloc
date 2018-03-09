/*
** tool.c for tool in /home/meghenr/PSU_2016_malloc/src
**
** Made by meghenr
** Login   <riadh.meghenem@epitech.net>
**
** Started on  Mon Feb  6 14:51:44 2017 meghenr
** Last update Sun Feb 12 18:54:16 2017 meghenr
*/

#include <stdlib.h>
#include <stdio.h>
#include "data.h"

void		lock_thread(pthread_mutex_t *mutex)
{
  if ((pthread_mutex_lock(mutex)) != 0)
    {
      fprintf(stderr, "Mutext lock failed\n");
      exit(1);
    }
}

void		unlock_thread(pthread_mutex_t *mutex)
{
  if ((pthread_mutex_unlock(mutex)) != 0)
    {
      fprintf(stderr, "Mutext unlock failed\n");
      exit(1);
    }
}
