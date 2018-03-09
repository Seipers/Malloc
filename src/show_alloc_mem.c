/*
** show_alloc_mem.c for show_alloc_mem in /home/meghenr/PSU_2016_malloc/src
**
** Made by meghenr
** Login   <riadh.meghenem@epitech.eu>
**
** Started on  Sun Feb 12 18:45:16 2017 meghenr
** Last update Sun Feb 12 20:43:41 2017 Sebastien Le Guischer
*/

#include <stdio.h>
#include "data.h"

void		show_alloc_mem()
{
  t_data	*tmp;

  printf("break: %p\n", sbrk(0));
  if (g_mem != NULL)
    {
      tmp = g_mem;
      while (tmp != NULL)
	{
	  if (tmp->next != NULL)
	    {
	      printf("%p - %p : %d bytes\n", tmp->data,
		     tmp->next, (int)tmp->size);
	    }
	  else
	    {
	      printf("%p - %p : %d bytes\n", tmp->data,
		     sbrk(0), (int)tmp->size);
	    }
	  tmp = tmp->next;
	}
    }
}
