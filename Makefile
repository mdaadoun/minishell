# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 07:46:55 by dlaidet           #+#    #+#              #
#    Updated: 2022/07/28 12:02:55 by dlaidet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#CONFIG
VAL	= 

NAME	= minishell

# **************************************************************************** #
#MANDATORY
M_PATH_SRCS	= main.c

M_PATH_DIR = src/

M_PATH	= $(addprefix $(M_PATH_DIR), $(M_PATH_SRCS))

M_OBJS	= ${M_PATH:.c=.o}
# **************************************************************************** #
#UTILS
CC	= gcc

LIBNAME = libft.a

LIBFTPATH = ../libft/

CFLAGS	= -Wall -Wextra -Werror
# **************************************************************************** #
#VALGRIND
V_ARG	= --track-origins=yes --leak-check=full --show-leak-kinds=all -s
# **************************************************************************** #

all:	${NAME}

${NAME}:	${M_OBJS}
	make -C ${LIBFTPATH}
	mv $(LIBFTPATH)${LIBNAME} ${LIBNAME}
	${CC} ${CFLAGS} -o ${NAME} ${M_OBJS} ${LIBNAME} -L/usr/local/lib -I/usr/local/include -lreadline

clean:
	rm -f ${M_OBJS}
	
fclean:	clean
	rm -f ${NAME} ${LIBNAME}
	make fclean -C ${LIBFTPATH}

re:	fclean all

gdb:	${M_OBJS}
	make -C ${LIBFTPATH}
	mv $(LIBFTPATH)${LIBNAME} ${LIBNAME}
	${CC} ${CFLAGS} -g -o ${NAME} ${M_OBJS} ${LIBNAME}

run:
	./${NAME} ${VAL}

val:
	valgrind $(V_ARG) ./${NAME} ${VAL}

.PHONY:	all clean fclean re val run gdb
