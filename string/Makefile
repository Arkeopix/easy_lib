NAME	=	test
GCC		=	gcc
SRC		=	easy_string.c
OBJ		=	${SRC:.c=.o}
CFLAGS	=	-Wall -ansi -pedantic -std=c99 -ggdb

${NAME}:	${OBJ}
			${GCC} ${OBJ} -o ${NAME} ${CFLAGS}

all:		${NAME}

clean:
			rm -vf ${OBJ}

fclean:		clean
			rm -vf ${NAME}

re:			fclean all
