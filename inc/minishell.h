/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:06:13 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/03 11:39:48 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// libraries

# include "libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <error.h>
# include <getopt.h>
# include <signal.h>

// types

typedef signed char			t_int8;
typedef unsigned char		t_uint8;
typedef signed short		t_int16;
typedef unsigned short		t_uint16;
typedef signed long			t_int32;
typedef unsigned long		t_uint32;
typedef signed long long	t_int64;
typedef unsigned long long	t_uint64;


// Minishell main structure:

# define MINISHELL_LOGO "\
=================================================================== \n\
███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗ \n\
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║ \n\
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║ \n\
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║ \n\
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗ \n\
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ \n\
=================================================================== \n\n"\

/*
 *	Elements:
 *		name:	shell name.
 *		path:	the current working directory.
 *		line:	last line read from input.
*/
typedef struct e_minishell {
	char	            *cwd_path;
	char	            **bin_paths;
	char	            *line;
    struct s_token      *first_token;
    struct s_variable   *first_var;
}           t_minishell;

/*
 *  Errors structures:
*/

# define MSG_ERROR_PARAMS "Minishell don't take any parameter."
# define MSG_ERROR_ALLOC "An error with memory allocation occured."
# define MSG_ERROR_COMMAND "The command is not found."
# define MSG_ERROR_UNKNOWN "Error."

typedef enum e_error {
    SUCCESS,
    ERROR_PARAMS,
    ERROR_ALLOC,
    ERROR_COMMAND,
    ERROR_UNKNOWN
}           t_error;


/*
 * Main functions
 *		files:
 *			core/ms_main.c
*/

void	ms_initialize_minishell(t_minishell **ms);


/*
 *  Builtin shell commands:
 *		files :	
 *			core/builtin/ms_cd.c
 *			core/builtin/ms_echo.c
 *			core/builtin/ms_env.c
 *			core/builtin/ms_exit.c
 *			core/builtin/ms_export.c
 *			core/builtin/ms_pwd.c
 *			core/builtin/ms_unset.c
*/

t_uint8	ms_echo(char **args, char option);
t_uint8	ms_cd(char **args);
t_uint8	ms_pwd(char **args);

typedef struct s_variable {
    char                *name;
    char                *content;
    struct s_variable   *next;
}   t_variable;

t_uint8	ms_export(char **args);
t_uint8	ms_unset(char **args);
t_uint8	ms_env(char **args);
t_uint8	ms_exit(void);

/*
 *  Signal handling:
 *      Files :
 *			core/executer/ms_events.c
*/

void	handle_signals(int signo);

/*
 *  Parser:
 *      Files :
 *			core/parser/ms_parser.c
 *			core/parser/ms_tokenization.c
 *          
*/

typedef enum e_token_type
{
    NO_TYPE,
    ARG_STRING,
    ARG_OPTION,
    PIPE,
    EXTERNAL_COMMAND,
    BUILTIN_COMMAND,
    REDIRECTION_LEFT,
    REDIRECTION_DOUBLE_LEFT,
    REDIRECTION_RIGHT,
    REDIRECTION_DOUBLE_RIGHT,
    AND,
    OR,
    WILDCARD
}   t_token_type;

typedef struct s_token
{
    char				*content;
    enum e_token_type   type;
    struct s_token		*prev;
    struct s_token		*next;
}           t_token;

void	ms_parser(t_minishell *ms);
void	ms_check_quotes(char *str);
t_token *ms_create_new_token(t_minishell *ms);
void	ms_add_token(t_minishell *ms, char* content, t_token_type type);
void    ms_append_token(t_token *before_token, t_token *add_token);
void	ms_free_all_tokens(t_minishell *ms);

void	ms_swap_env(t_minishell *ms);

/*
 *  Lexical Analyzer:
 *      Files :
 *          core/lexer/ms_lexer.c
 *          core/lexer/ms_command.c
*/

void	ms_lexer(t_minishell *ms);
bool    ms_is_valid_command(t_minishell *ms);
// void	ms_replace_variables(t_minishell *ms);

/*
 *  Evaluation executer:
*/

void	ms_executer(t_minishell *ms);

/*
 *	Errors and memory:
 *		files :	
 *			core/parser/ms_errors.c
 *			core/executor/ms_free.c
*/

int		ms_free_before_exit(t_minishell *ms, int err_key);
void	ms_free_last_command(t_minishell *ms);

/*
 *  Debug variables and functions:
 *		files :	
 *			test/test_builtin.c
 *			test/test_main.c
*/

#ifndef DEBUG
# define DEBUG 0
#endif

void 	run_test(int argc, char **argv, char **envp);
void 	test_builtin(int argc, char **argv, char **envp);
void	test_parser(t_minishell *ms);

#endif
