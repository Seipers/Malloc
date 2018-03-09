##
## Makefile for malloc in /home/sebastien/Rendu/PSU_2016_malloc
## 
## Made by Sebastien Le Guischer
## Login   <sebastien@epitech.net>
## 
## Started on  Thu Feb  2 14:22:37 2017 Sebastien Le Guischer
## Last update Sun Feb 12 18:57:11 2017 meghenr
##

NAME		= libmy_malloc.so

SRC		= src

SRCS		= $(SRC)/malloc.c\
		  $(SRC)/free.c\
		  $(SRC)/realloc.c\
		  $(SRC)/tool.c\
		  $(SRC)/show_alloc_mem.c

OBJS		= $(SRCS:.c=.o)

CFLAGS		= -W -Wall -Wextra -Werror -fPIC

RM		= rm -rf

GCC		= gcc

all:		$(NAME)

$(NAME):	$(OBJS)
	$(GCC) -shared -o $(NAME) $(OBJS)

export:		$(NAME)
	export LD_PRELOAD=./$(NAME)

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
