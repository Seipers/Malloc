/*
** test.c for malloc in /home/meghenr/PSU_2016_malloc/new_malloc
**
** Made by meghenr
** Login   <riadh.meghenem@epitech.eu>
**
** Started on  Wed Feb  1 13:04:39 2017 meghenr
** Last update Sun Feb 12 20:38:48 2017 Sebastien Le Guischer
*/

#include <string.h>
#include <stdio.h>
#include <sys/sysinfo.h>
#include "data.h"

pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t	g_mutex2 = PTHREAD_MUTEX_INITIALIZER;
t_data		*g_mem = NULL;

static t_data		*find_space(size_t size)
{
  t_data		*tmp;

  tmp = g_mem;
  while (tmp != NULL)
    {
      if (tmp->size >= size && tmp->state == FREE)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

static t_data		*find_last()
{
  t_data		*tmp;

  if (g_mem == NULL)
    return (NULL);
  tmp = g_mem;
  while (tmp->next != NULL)
    tmp = tmp->next;
  return (tmp);
}

static int		new_page(size_t size)
{
  int			i;
  t_data		*last;

  i = 1;
  while ((i * PAGE_SIZE) - DATA_SIZE < size)
    i = i + 1;
  last = sbrk(0);
  if (sbrk(i * PAGE_SIZE) == (void *) -1)
      return (1);
  last->size = (i * PAGE_SIZE) - DATA_SIZE;
  last->next = NULL;
  last->prev = find_last();
  last->state = FREE;
  if (last->prev != NULL)
    last->prev->next = last;
  else
    g_mem = last;
  return (0);
}

static t_data		*split_block(size_t size)
{
  t_data		*tmp;
  t_data		*new;

  tmp = find_space(size);
  if (tmp->size > size + DATA_SIZE)
    {
      new = (t_data *)(tmp->data + size);
      new->size = tmp->size - DATA_SIZE - size;
      new->prev = tmp;
      new->next = tmp->next;
      new->state = FREE;
      tmp->size = size;
      tmp->next = new;
      if (new->next != NULL)
	new->next->prev = new;
    }
  tmp->state = ALLOC;
  return (tmp);
}

void			*malloc(size_t size)
{
  t_data		*mem;
  struct sysinfo	info;

  sysinfo(&info);
  if ((size > info.freeram))
    return (NULL);
  lock_thread(&g_mutex);
  if (g_mem == NULL || find_space(size) == NULL)
    if (new_page(size) == 1)
      {
        unlock_thread(&g_mutex);
	return (NULL);
      }
  mem = split_block(size);
  unlock_thread(&g_mutex);
  return ((void *)mem->data);
}
