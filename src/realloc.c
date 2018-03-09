/*
** realloc.c for realloc in /home/meghenr/PSU_2016_malloc/new_malloc
**
** Made by meghenr
** Login   <riadh.meghenem@epitech.eu>
**
** Started on  Thu Feb  2 14:26:20 2017 meghenr
** Last update Sun Feb 12 20:31:38 2017 meghenr
*/

#include <string.h>
#include "data.h"

static void	cpy_data(void *src, void *dst)
{
  char		*dsrc;
  char		*ddst;
  t_data	*tsrc;
  t_data	*tdst;
  size_t	i;

  i = 0;
  dsrc = src;
  ddst = dst;
  tsrc = get_data(src);
  tdst = get_data(dst);
  while (i < tsrc->size && i < tdst->size)
  {
    ddst[i] = dsrc[i];
    i += 1;
  }
}

void		*realloc(void *ptr, size_t size)
{
  void		*new;
  t_data	*tmp;

  if (ptr == NULL)
    return (malloc(size));
  if (size == 0)
    return (NULL);
  lock_thread(&g_mutex2);
  tmp = get_data(ptr);
  if (tmp->size > size)
    {
      unlock_thread(&g_mutex2);
      return (ptr);
    }
  if ((new = malloc(size)) == NULL)
    {
      unlock_thread(&g_mutex2);
      return (NULL);
    }
  tmp = get_data(new);
  tmp->size = size;
  cpy_data(ptr, new);
  free(ptr);
  unlock_thread(&g_mutex2);
  return (new);
}

void		*calloc(size_t nmemb, size_t size)
{
  void		*new;

  if ((new = malloc(nmemb * size)) == NULL)
    return (NULL);
  bzero(new, (size * nmemb));
  return (new);
}
