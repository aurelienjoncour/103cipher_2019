##
## EPITECH PROJECT, 2019
## 103cipher
## File description:
## Makefile
##

CC	=	gcc

RM	=	rm -f

SRC	=	main.c				\
		error_handling.c	\
		encryption.c		\
		decryption.c		\
		my_str_to_word_array.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -lm -g -I./include

NAME	=	103cipher

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME) -lm

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
