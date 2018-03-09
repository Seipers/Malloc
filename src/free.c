/*
** free.c for free in /home/meghenr/PSU_2016_malloc/new_malloc
**
** Made by meghenr
** Login   <riadh.meghenem@epitech.eu>
**
** Started on  Wed Feb  1 11:20:20 2017 meghenr
** Last update Sun Feb 12 18:58:55 2017 meghenr
*/

#include <stdio.h>
#include <stdlib.h>
#include "data.h"

int	own_alloc(void *ptr)
{
  if (ptr != NULL && ((t_data *)ptr > g_mem && ptr < sbrk(0)))
    return (0);
  return (1);
}

t_data	*get_data(void *ptr)
{
  return ((t_data *)((char*)ptr - DATA_SIZE + 4));
}

void		free(void *ptr)
{
  t_data	*mem;

  if (own_alloc(ptr) == 0)
    {
      lock_thread(&g_mutex);
      mem = get_data(ptr);
      if (mem->state == FREE)
	{
	  fprintf(stderr, "Error, Not enough memory\n");
	  abort();
	}
      mem->state = FREE;
      unlock_thread(&g_mutex);
    }
}
