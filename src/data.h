/*
** data.h for malloc in /home/sebastien/Rendu/malloc
**
** Made by Sebastien Le Guischer
** Login   <sebastien.le-guischer@epitech.eu>
**
** Started on  Tue Jan 31 15:14:01 2017 Sebastien Le Guischer
** Last update Sun Feb 12 20:36:06 2017 Sebastien Le Guischer
*/

#ifndef DATA_H_
# define DATA_H_

# include <pthread.h>
# include <unistd.h>

typedef enum	e_state
  {
    ALLOC,
    FREE
  }		t_state;

typedef struct	s_data
{
  size_t	size;
  struct s_data	*prev;
  struct s_data	*next;
  t_state	state;
  char		data[1];
}		t_data;

extern	pthread_mutex_t	g_mutex;
extern	pthread_mutex_t	g_mutex2;
extern	t_data		*g_mem;

# define PAGE_SIZE getpagesize()
# define DATA_SIZE sizeof(t_data)

void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);
void	*calloc(size_t, size_t);
int	own_alloc(void  *ptr);
t_data	*get_data(void *ptr);
void	show_alloc_mem();
void	lock_thread(pthread_mutex_t *mutex);
void	unlock_thread(pthread_mutex_t *mutex);

#endif /* !DATA_H_ */
