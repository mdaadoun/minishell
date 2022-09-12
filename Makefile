# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/20 08:44:56 by mdaadoun          #+#    #+#              #
#    Updated: 2022/09/12 14:56:53 by mdaadoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = ms_main.c \
utils/ms_utils_free.c utils/ms_utils_errors.c \
utils/ms_utils_extra.c utils/ms_utils_tokenizer.c \
utils/ms_utils_variable.c utils/ms_utils_processes.c utils/ms_utils_signals.c \
utils/ms_utils_env.c utils/ms_sorting_env.c utils/ms_utils_is.c\
utils/ms_utils_redirection.c utils/ms_utils_pipe.c\
builtins/ms_cd.c builtins/ms_echo.c builtins/ms_env.c builtins/ms_exit.c \
builtins/ms_export.c builtins/ms_pwd.c builtins/ms_unset.c \
parser/ms_parser.c parser/ms_parse_pipes.c \
parser/ms_parse_variables.c parser/ms_parse_quotes.c parser/ms_parse_redirections.c \
analyzer/ms_analyzer.c analyzer/ms_analyze_command.c analyzer/ms_analyze_pipes.c \
analyzer/ms_analyze_redirections.c analyzer/ms_analyze_arguments.c \
executer/ms_executer.c executer/ms_build_redirections.c \
executer/ms_build_processes.c executer/ms_run_processes.c \
executer/ms_redirection_struct.c 

DIR = src
OBJS = $(addprefix $(DIR)/,$(SRCS:%.c=%.o))
DIR_LIB = libft
LIBFT = $(DIR_LIB)/libft.a
CC = gcc
AR = ar rcs
RM = rm -f
FLAGS = -Wall -Wextra -Werror
READLINE_FLAGS = -L/usr/local/lib -I/usr/local/include -lreadline
V_ARG	=  --suppressions=.valgrind_ignore_readline --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s 


R = \033[38;5;1m
G = \033[38;5;2m
B = \033[38;5;4m
D = \033[38;5;255m

.c.o:
	@$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	@make -sC libft
	@echo "$(B)Building $(NAME) program.$(D)"
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(READLINE_FLAGS)
	@echo "$(G)$(NAME) program created.$(D)"

clean:
	@echo "$(R)Remove all object files.$(D)"
	@$(RM) $(OBJS)
	@make clean -sC libft

fclean: clean
	@echo "$(R)Remove $(NAME) program if present.$(D)"
	@$(RM) $(NAME)
	@make fclean -sC libft

re: fclean all

valgrind:
	@echo "$(B)Starting memory test.$(D)"
	valgrind $(V_ARG) ./$(NAME)
	@echo "$(G)Test done.$(D)"

run:
	./${NAME}

.PHONY:  all clean fclean re run valgrind
