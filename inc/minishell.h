/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:06:13 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/08 18:06:54 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// libraries

# include "libft.h"
# include <stdio.h>
# include <limits.h>
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

// logo

# define MINISHELL_LOGO "\
\e[0;38m+=====================================================================+\e[m\n\
\e[0;38m|\e[m\e[1;34m             :            .                                          \e[m\e[0;38m|\e[m\n\
\e[0;38m|\e[m\e[1;34m ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗      \e[m\e[0;38m|\e[m\n\
\e[0;38m|\e[m\e[1;36m ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║      \e[m\e[0;38m|\e[m\n\
\e[0;38m|\e[m\e[1;36m ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║      \e[m\e[0;38m|\e[m\n\
\e[0;38m|\e[m\e[1;36m ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║      \e[m\e[0;38m|\e[m\n\
\e[0;38m|\e[m\e[1;34m ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗ \e[m\e[0;38m|\e[m\n\
\e[0;38m|\e[m\e[1;34m ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ \e[m\e[0;38m|\e[m\n\
\e[0;38m\\=========================\e[0;34mm\e[m\e[0;36mdaadoun\e[m&&\e[0;34md\e[m\e[0;36mlaidet\e[m===========================/\e[m\n\n"\

// Minishell main structure:

/*
 *	Elements:
 *		name:	shell name.
 *		path:	the current working directory.
 *		line:	last line read from input.
*/
typedef struct s_minishell {
	int					error;
	char				*cwd_path;
	char				**bin_paths;
	char				**envp;
	char				*full_command;
	bool				has_pipe;
	struct s_token		*first_token;
	struct s_variable	*first_var;
	struct s_processes	*processes;
}	t_minishell;

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

typedef enum e_builtins {
    BIN_NULL,
    BIN_ECHO,
    BIN_CD,
    BIN_PWD,
    BIN_EXPORT,
    BIN_UNSET,
    BIN_ENV,
    BIN_EXIT,
    BIN_HISTORY,
}   t_builtins;

typedef struct s_variable {
	char				*name;
	char				*content;
	struct s_variable   *next;
}   t_variable;

t_uint8	ms_echo(char **args, char option);
t_uint8	ms_cd(char **args);
t_uint8	ms_pwd(void);
t_uint8	ms_export(t_minishell *ms, char *cmd);
t_uint8	ms_unset(char **args);
t_uint8	ms_env(t_minishell *ms);
void	ms_exit(t_minishell *ms);

/*
 *  Signal handling:
 *		Files :
 *			core/executer/ms_events.c
*/

void	ms_initialize_signals(void);

/*
 *  Tokens:
 *      Files :
 *			core/parser/ms_tokenization.c
 *          
*/

typedef enum e_token_type
{
	NO_TYPE,
	TYPE_ARG_STRING,
	TYPE_ARG_OPTION,
	TYPE_PIPE,
	TYPE_EXTERNAL_COMMAND,
	TYPE_BUILTIN_COMMAND,
	TYPE_REDIRECT_LEFT,
	TYPE_REDIRECT_DOUBLE_LEFT,
	TYPE_REDIRECT_RIGHT,
	TYPE_REDIRECT_DOUBLE_RIGHT,
	TYPE_AND,
	TYPE_OR,
	TYPE_WILDCARD
}	t_token_type;

typedef struct s_token
{
	char				*content;
	enum e_token_type	type;
	t_builtins			builtin;
	struct s_token		*prev;
	struct s_token		*next;
}           t_token;

void	ms_replace_token(t_token *old, t_token *new);
t_token	*ms_delete_token(t_token *token);
void	ms_add_token(t_minishell *ms, char* content, t_token_type type);
void	ms_append_token(t_token *before_token, t_token *add_token);

/*
 *  Parser:
 *      Files :
 *			core/parser/ms_parser.c
 *			core/parser/ms_parse_variables.c
 *			core/parser/ms_parse_quotes.c
 *			core/parser/ms_parse_pipes.c
 *          
*/

void	ms_parser(t_minishell *ms);
void	ms_check_quotes(char *str);
t_token	*ms_create_new_token(t_minishell *ms);
void	ms_parse_quotes(t_minishell *ms);
void	ms_swap_env(t_minishell *ms);
void	ms_parse_pipe(t_minishell *ms);
void	ms_parse_redirections(t_minishell *ms);

/*
 *  Lexical Analyzer:
 *      Files :
 *          core/lexer/ms_lexer.c
 *          core/lexer/ms_analyze_command.c
 *          core/lexer/ms_analyze_pipes.c
*/

void	ms_lexer(t_minishell *ms);
void	ms_analyze_command(t_minishell *ms, t_token *cmd);
void	ms_analyze_pipes(t_minishell *ms);

/*
 *  Evaluation executer:
 *      Files :
 *			core/executer/ms_executer.c
 *			core/executer/ms_processes.c
*/

typedef struct s_processes {
	t_uint8				nb_process;
	struct s_command	*first_command;
}   t_processes;

typedef struct s_command {
	char	*command_line;
	pid_t	process_id;
}   t_command;

void	ms_executer(t_minishell *ms);
void	ms_start_processes(t_minishell *ms);
void	ms_build_processes(t_minishell *ms);
void	ms_free_processes(t_minishell *ms);

/*
 *	Memory:
 *		files :	
 *			core/executer/ms_free.c
*/

int		ms_free_before_exit(t_minishell *ms, int err_key);
void	ms_free_last_command(t_minishell *ms);
void	ms_free_all_tokens(t_minishell *ms);

/*
 *	Errors:
 *		files :	
 *			core/errors/ms_errors.c
*/

void ms_checking_for_errors(t_minishell *ms);

/*
 *  Debug variables and functions:
 *		files :	
 *			test/test_builtin.c
 *			test/test_main.c
*/

typedef enum e_tests
{
	NO_TEST,
	TEST_PARSER = 1,
	TEST_LEXER = 2,
	TEST_BUILTIN = 3,
	TEST_EXECUTER = 4,
	TEST_PARSER_QUOTES = 11,
	TEST_PARSER_PIPES = 12,
	TEST_PARSER_ENV = 13,
	TEST_PARSER_REDIRECT = 14,
	TEST_LEXER_BUILTINS = 21,
	TEST_LEXER_EXTERNALS = 22,
	TEST_LEXER_PIPES = 23,
	TEST_BUILTIN_PWD = 31,
	TEST_BUILTIN_ENV = 32,
	TEST_BUILTIN_EXPORT = 33,
	TEST_EXECUTER_PROCESSES_BUILD = 41
}   t_tests;

#ifndef DEBUG
# define DEBUG 0
#endif

void	display_tokens(t_minishell *ms);
void 	run_test(int argc, char **argv, char **envp);
void	test_builtin(t_minishell *ms, int debug);
void	test_lexer(t_minishell *ms, int debug);
void	test_parser(t_minishell *ms, int debug);
void	test_executer(t_minishell *ms, int debug);

#endif
