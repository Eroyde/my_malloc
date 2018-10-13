##
## EPITECH PROJECT, 2017
## my_malloc
## File description:
## Makefile to build the project
##

NAME		=	libmy_malloc.so

SRC		=	src/malloc.c		\
			src/free.c		\
			src/block.c		\
			src/realloc.c		\
			src/show_alloc_mem.c	\
			src/list_metadata.c

OBJ		=	$(SRC:.c=.o)

INC		=	-I include/

CFLAGS		+=	-W -Wall -Wextra -std=gnu99 -fpic -Ofast $(INC)

LIB		=	-lpthread

LDFLAGS		+=	-shared $(LIB)

RM		=	rm -f

all:			$(NAME)

$(NAME):		$(OBJ)
			$(CC) $(LDFLAGS) $(OBJ) -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean:			clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:			clean fclean all re
