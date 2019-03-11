##
## EPITECH PROJECT, 2018
## PSU_2017_malloc
## File description:
## Makefile
##

SRC	=	malloc.c	\
		free.c		\
		realloc.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	+=	-Wall -Wextra

RM	=	rm -rf

CC	=	gcc

NAME	=	libmy_malloc.so

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -c $(CFLAGS) -fpic $(SRC)
	$(CC) -shared -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
