# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/20 08:44:56 by mdaadoun          #+#    #+#              #
#    Updated: 2022/08/01 10:22:49 by mdaadoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_printf/ft_printf.c ft_printf/ft_putbase.c ft_printf/ft_printf_utils.c \
ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
ft_strrchr.c ft_tolower.c ft_toupper.c ft_isspace.c ft_calloc.c ft_strdup.c \
ft_isupper.c ft_islower.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
get_next_line/get_next_line.c get_next_line/get_next_line_utils.c ft_dlstnew.c ft_dlstadd_back.c \
ft_dlstlast.c ft_lstnew_str.c ft_lstdelone_str.c ft_lstclear_str.c ft_lstadd_back_str.c ft_lstlast_str.c

INC = ../../inc/libft.h

OBJS = ${SRCS:.c=.o}

CC = gcc

AR = ar rcs

RM = rm -f

FLAGS = -Wall -Wextra -Werror

DEBUG_FLAGS = -g3 -ggdb -I.

R = \033[38;5;1m
G = \033[38;5;2m
B = \033[38;5;4m
D = \033[38;5;255m

.c.o:
	@$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS) $(INC)
	@echo "$(B)Building libraries.$(D)"
	@$(AR) $(NAME) $(OBJS)
	@echo "$(G)$(NAME) created.$(D)"

all: $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@echo "$(R)Remove $(NAME) library.$(D)"
	@$(RM) $(NAME)

re: fclean all

.PHONY:  all clean fclean re 
