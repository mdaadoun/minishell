# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/20 08:44:56 by mdaadoun          #+#    #+#              #
#    Updated: 2022/08/02 09:05:35 by mdaadoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = ms_main.c \
builtin/ms_cd.c builtin/ms_echo.c builtin/ms_env.c builtin/ms_exit.c \
builtin/ms_export.c builtin/ms_pwd.c builtin/ms_unset.c \
executer/ms_executer.c executer/ms_free.c \
parser/ms_parser.c \
lexer/ms_lexer.c \
parser/ms_errors.c
DIR = src/core
OBJS = $(addprefix $(DIR)/,$(SRCS:%.c=%.o))
DIR_LIB = src/libft
LIBFT = $(DIR_LIB)/libft.a
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
DIR_BONUS = src/bonus
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


DEBUG_SRCS = ft_printf/ft_printf.c ft_printf/ft_putbase.c ft_printf/ft_printf_utils.c \
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


DEBUG_FLAGS = -g3 -ggdb -I. -fsanitize=address -D DEBUG=1 # -fsanitize=leak
V_ARG	= --track-origins=yes --leak-check=full --show-leak-kinds=all -s
TEST_SRCS = src/test/test_builtin.c src/test/test_main.c

ARGS = 

debug: fclean
	@echo "$(B)Starting debug compilation.$(D)"
	@$(CC) $(DEBUG_FLAGS) $(addprefix $(DIR)/,$(SRCS)) $(TEST_SRCS) $(addprefix $(DIR_LIB)/,$(DEBUG_SRCS)) -o $(NAME) $(READLINE_FLAGS) 
	@echo "$(G)$(NAME) debug program created.$(D)"

valgrind: debug
	@echo "$(B)Starting memory test.$(D)"
	valgrind $(V_ARG) ./$(NAME)
	@echo "$(G)Test done.$(D)"

debug_bonus: fclean
	@echo "$(B)Starting debug compilation.$(D)"
	@$(CC) $(DEBUG_FLAGS) $(addprefix $(DIR)/,$(SRCS)) $(TEST_SRCS) $(addprefix $(DIR_LIB)/,$(DEBUG_SRCS)) -o $(NAME_BONUS) $(READLINE_FLAGS)
	@echo "$(G)$(NAME_BONUS) debug program created.$(D)"

valgrind_bonus: debug_bonus
	@echo "$(B)Starting memory test.$(D)"
	valgrind $(V_ARG) ./$(NAME_BONUS)
	@echo "$(G)Test done.$(D)"

run:
	./${NAME} ${ARGS}

.PHONY:  all clean fclean re run bonus debug test debug_bonus test_bonus
