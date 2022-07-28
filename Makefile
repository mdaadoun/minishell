# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/20 08:44:56 by mdaadoun          #+#    #+#              #
#    Updated: 2022/07/28 14:28:25 by mdaadoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = ms_main.c
DIR = src
OBJS = $(addprefix $(DIR)/,$(SRCS:%.c=%.o))
LIBFT = $(DIR)/libft/libft.a
CC = gcc
AR = ar rcs
RM = rm -f
FLAGS = -Wall -Wextra -Werror 
READLINE_FLAGS = -L/usr/local/lib -I/usr/local/include -lreadline

R = \033[38;5;1m
G = \033[38;5;2m
B = \033[38;5;4m
D = \033[38;5;255m

.c.o:
	@$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

all: build_lib $(NAME)

$(NAME): $(OBJS)
	@echo "$(B)Building $(NAME) program.$(D)"
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(READLINE_FLAGS)
	@echo "$(G)$(NAME) program created.$(D)"

build_lib:
	@make -sC src/libft

NAME_BONUS = minishell_bonus
SRCS_BONUS = ms_main_bonus.c
DIR_BONUS = bonus
OBJS_BONUS = $(addprefix $(DIR_BONUS)/,$(SRCS_BONUS:%.c=%.o))

$(NAME_BONUS): $(OBJS_BONUS)
	@echo "$(B)Building $(NAME_BONUS) program.$(D)"
	@$(CC) $(FLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS) $(READLINE_FLAGS)
	@echo "$(G)$(NAME_BONUS) program created.$(D)"

bonus: build_lib $(NAME_BONUS)

clean:
	@echo "$(R)Remove all object files.$(D)"
	@$(RM) $(OBJS) $(OBJS_BONUS) 
	@make clean -sC src/libft

fclean: clean
	@echo "$(R)Remove $(NAME) and $(NAME_BONUS) programs if present.$(D)"
	@$(RM) $(NAME) $(NAME_BONUS)
	@make fclean -sC src/libft

re: fclean all

## DEBUG SECTION

DEBUG_FLAGS = -g3 -ggdb -I. -fsanitize=address # -fsanitize=leak
V_ARG	= --track-origins=yes --leak-check=full --show-leak-kinds=all -s
DIR_LIB = src/libft
ARGS =

debug: fclean
	@make debug -sC src/libft
	@echo "$(B)Starting debug compilation.$(D)"
	@$(CC) $(FLAGS) $(DEBUG_FLAGS) $(addprefix $(DIR)/,$(SRCS)) $(addprefix $(DIR_LIB)/,$(SRCS_LIB)) $(MLIBX) -lXext -lX11  -o $(NAME)
	@echo "$(G)$(NAME) debug program created.$(D)"

test: debug
	@echo "$(B)Starting memory test.$(D)"
	valgrind $(V_ARG) ./$(NAME)
	@echo "$(G)Test done.$(D)"

debug_bonus: fclean
	@make debug -sC src/libft
	@echo "$(B)Starting debug compilation.$(D)"
	@$(CC) $(FLAGS) $(DEBUG_FLAGS) $(addprefix $(DIR_BONUS)/,$(SRCS_BONUS)) $(addprefix $(DIR_LIB)/,$(SRCS_LIB)) $(MLIBX) -lXext -lX11  -o $(NAME_BONUS)
	@echo "$(G)$(NAME_BONUS) debug program created.$(D)"

test_bonus: debug_bonus
	@echo "$(B)Starting memory test.$(D)"
	valgrind $(V_ARG) ./$(NAME_BONUS)
	@echo "$(G)Test done.$(D)"

run:
	./${NAME} ${ARGS}

.PHONY:  all clean fclean re debug test start bonus
