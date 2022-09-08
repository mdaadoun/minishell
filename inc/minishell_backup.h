/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:06:13 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/08 07:45:46 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//==========
// Libraries
//==========

# include "libft.h"
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <error.h>
# include <getopt.h>
# include <signal.h>
# include <assert.h>
# include <sys/types.h>
# include <sys/wait.h>       
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>

//======
// Types
//======

typedef signed char			t_int8;
typedef unsigned char		t_uint8;
typedef signed short		t_int16;
typedef unsigned short		t_uint16;
typedef signed long			t_int32;
typedef unsigned long		t_uint32;
typedef signed long long	t_int64;
typedef unsigned long long	t_uint64;

//=====
// Logo
//=====

# define MINISHELL_LOGO "\
\e[0;38m+=====================================================================+\e[m\n\
\e[0;38m|\e[m\e[1;34m             :            .                                          \e[m\e[0;38m|\e[m\n\
\e[0;38m|\e[m\e[1;34m ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗      \e[m\e[0;38m|\e[m\n\
\e[0;38m|\e[m\e[1;36m ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║      \e[m\e[0;38m|\e[m\n\
\e[0;38m|\e[m\e[1;36m ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║      \e[m\e[0;38m|\e[m\n\
\e[0;38m|\e[m\e[1;36m ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║      \e[m\e[0;38m|\e[m\n\
\e[0;38m|\e[m\e[1;34m ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗ \e[m\e[0;38m|\e[m\n\
\e[0;38m|\e[m\e[1;34m ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ \e[m\e[0;38m|\e[m\n\
\e[0;38m\\=========================\
\e[0;34mm\e[m\e[0;36mdaadoun\e[m&&\e[0;34md\e[m\e[0;36mlaidet\e[m\
===========================/\e[m\n\n"

//=====================
// Minishell structures
//=====================

/*
 *	Errors structures:
*/

# define MSG_ERROR_MALLOC "An error with memory allocation occured."
# define MSG_ERROR_PARAMS "Minishell don't take any parameter."
# define MSG_ERROR_COMMAND "The command doesn't exist."
# define MSG_ERROR_BUILTIN_OPTION "The option is not valid."
# define MSG_ERROR_BUILTIN_ARGUMENT "The arguments are not valid."
# define MSG_ERROR_MISSING_ARGS "There is not enough arguments."
# define MSG_ERROR_EXTRA_ARGS "There is too many arguments."
# define MSG_ERROR_SYNTAX_PIPE "The syntax with pipes is not valid."
# define MSG_ERROR_SYNTAX_REDIRECT "The syntax with redirections is not valid."
# define MSG_ERROR_PATH "No such file or directory."
# define MSG_ERROR_EXPORT "Not a valid identifier to export."
# define MSG_ERROR_EXIT_ARG "Numeric argument expected."

typedef enum e_err_key {
	NO_ERROR,
	ERROR_PARAMS,
	ERROR_MALLOC,
	ERROR_COMMAND,
	ERROR_BUILTIN_OPTION,
	ERROR_BUILTIN_ARGUMENT,
	ERROR_MISSING_ARGS,
	ERROR_EXTRA_ARGS,
	ERROR_SYNTAX,
	ERROR_EXPORT,
	ERROR_PATH,
	ERROR_SILENT,
	ERROR_EXIT_ARG
}			t_err_key;

typedef struct s_error {
	bool		flag;
	char		*msg;
	int			length;
	t_err_key	key;
}				t_error;

/*
 *	Main structure:
 *		cwd_path:		the current working directory.
 *		envp: 			the env data.
 *		full_command:	last line read from input.
 *		first_token:	the entry point to the token structure.
 *		first_process:	the entry point to the processes structure.
 *		first_var:		the entry point to the environment structure.
 *		global_error:	the shell global error structure.
 *		(see process internal errors)
*/

typedef struct s_minishell {
	char				**envp;
	char				*full_command;
	struct s_token		*first_token;
	struct s_variable	*first_var;
	struct s_process	*first_process;
	struct s_error		*global_error;
}	t_minishell;

/*
 *  Signal structure:
 *		Used to deal with Ctrl-C in the heredoc
*/

typedef struct s_signal {
	int		exit_status;
	char	*delimiter;
	bool	in_child;
	bool	in_heredoc;
	bool	in_process;
}	t_signal;

t_signal					g_sig;

/*
 *  Builtin commands structures:
*/

typedef enum e_builtins {
	BIN_NULL,
	BIN_ECHO,
	BIN_CD,
	BIN_PWD,
	BIN_EXPORT,
	BIN_UNSET,
	BIN_ENV,
	BIN_EXIT
}	t_builtins;

typedef struct s_variable {
	char				*name;
	char				*content;
	struct s_variable	*next;
}						t_variable;

/*
 *  Tokens structures:
*/

typedef enum e_token_type
{
	NO_TYPE,
	TYPE_S_QUOTE_STRING,
	TYPE_D_QUOTE_STRING,
	TYPE_ARG_STRING,
	TYPE_ARG_OPTION,
	TYPE_ARG_REDIRECT_FILE,
	TYPE_ARG_DELIMITER,
	TYPE_PIPE,
	TYPE_EXTERNAL_COMMAND,
	TYPE_BUILTIN_COMMAND,
	TYPE_BAD_COMMAND,
	TYPE_REDIRECT_LEFT,
	TYPE_REDIRECT_DOUBLE_LEFT,
	TYPE_REDIRECT_RIGHT,
	TYPE_REDIRECT_DOUBLE_RIGHT
}	t_token_type;

typedef struct s_token
{
	enum e_token_type	type;
	char				*content;
	char				*external_path;
	t_builtins			builtin;
	struct s_token		*prev;
	struct s_token		*next;
	bool				no_space;
}						t_token;

/*
 *  Executer structures:
*/

typedef struct s_redirection
{
	enum e_token_type		type;
	char					*filepath;
	int						fd;
	struct s_redirection	*next;
}						t_redirection;

typedef struct s_process {
	bool				has_redirection;
	t_redirection		*first_redirection;
	int					pipe_in;
	int					pipe_out;
	char				**cmd;
	char				*exec_path;
	char				**envp;
	t_token_type		*types_line;
	t_builtins			builtin;
	pid_t				pid;
	struct s_process	*prev;
	struct s_process	*next;
	t_error				*internal_error;
}						t_process;

//====================
// Minishell functions
//====================

void		ms_build_env_tab(t_minishell *ms);
t_variable	*ft_get_struct_env(t_minishell *ms, char *str);
size_t		ms_envlen(t_variable *env);
void		ms_sorting_env(t_minishell *ms);

/*
 * Main functions
 *		files:
 *			core/ms_main.c
*/

void		ms_initialize_minishell(t_minishell **ms, t_error *error, \
char **envp);

/*
 *	Errors functions:
 *		files :	
 *			core/utils/ms_utils_errors.c
*/

void		ms_checking_for_errors(t_minishell *ms);
void		ms_set_error(t_error *error, t_err_key err_key, char *err_msg);
void		ms_print_error(t_minishell *ms);

/*
 *	Environment functions:
 *		files :	
 *			core/utils/ms_utils_variable.c
*/

void		ms_copy_env(t_minishell *ms, char **envp);
char		*ft_get_env(t_minishell *ms, char *str);
void		ft_replace_variable(t_minishell *ms, t_variable *env);
void		ft_add_variable(t_minishell *ms, t_variable *env);
t_variable	*ft_create_variable(t_minishell *ms, char	*str);

/*
 *  Builtin commands functions:
 *		files :	
 *			core/builtin/ms_cd.c
 *			core/builtin/ms_echo.c
 *			core/builtin/ms_env.c
 *			core/builtin/ms_exit.c
 *			core/builtin/ms_export.c
 *			core/builtin/ms_pwd.c
 *			core/builtin/ms_unset.c
*/

void		ms_echo(char **arg);
void		ms_cd(t_minishell *ms, char **arg);
void		ms_pwd(t_minishell *ms, char **arg);
void		ms_export(t_minishell *ms, char **arg);
void		ms_unset(t_minishell *ms, char **arg);
void		ms_env(t_minishell *ms);
void		ms_exit(t_minishell *ms, char **arg);

/*
 *  Signal handling:
 *		Files :
 *			core/utils/ms_utils_signals.c.c
*/

void		ms_initialize_signals(void);

/*
 * 	Files :
 * 		core/utils/ms_utils_is.c
 */

bool		is_empty_command(t_minishell *ms);
bool		is_builtin_fork(t_builtins built);
int			is_redirect(t_token *tok);
bool		is_builtin(t_token *command, char *name_bin, t_builtins index_bin);
bool		check_if_builtin(t_token *command);

/*
 * Files :
 * 		core/utils/ms_utils_redirection.c
 */

bool		is_double_redirect(t_minishell *ms, char *str, int ind);
void		init_fd_redirection(t_process *proc);
void		set_redir_fd(t_redirection *redir);
int			get_len_redir(char *string, int start);

/*
 *  Tokens:
 *      Files :
 *			core/utils/ms_utils_tokenizer.c
 *			core/utils/ms_utils_extra.c
*/

t_token		*ms_create_new_token(t_minishell *ms);
void		ms_replace_token(t_token *old, t_token *new);
t_token		*ms_delete_token(t_token *token);
void		ms_add_token(t_minishell *ms, char *content,
				t_token_type type, bool no_space);
void		ms_push_token(t_token *first_token, t_token *second_token);
void		ms_combine_token(t_token *first_token, t_token *second_token);
void		ms_free_double_pointer(char **data);

/*
 *  Parser:
 *      Files :
 *			core/parser/ms_parser.c
 *			core/parser/ms_parse_variables.c
 *			core/parser/ms_parse_quotes.c
 *			core/parser/ms_parse_pipes.c
 *			core/parser/ms_parse_redirections.c
*/

void		ms_parser(t_minishell *ms);
void		ms_parse_quotes(t_minishell *ms, char *line, size_t ind);
void		ms_swap_env(t_minishell *ms);
void		ms_parse_pipes(t_minishell *ms);
void		ms_parse_redirections(t_minishell *ms);

/*
 *  Analyzer:
 *      Files :
 *          core/analyzer/ms_analyzer.c
 *          core/analyzer/ms_analyze_command.c
 *          core/analyzer/ms_analyze_pipes.c
 *          core/analyzer/ms_analyze_redirections.c
 *          core/analyzer/ms_analyze_arguments.c
*/

void		ms_analyzer(t_minishell *ms);
void		ms_analyze_command(t_minishell *ms, t_token *cmd);
void		ms_analyze_pipes(t_minishell *ms);
void		ms_analyze_redirections(t_minishell *ms);
void		ms_analyze_arguments(t_minishell *ms);

/*
 *  Evaluation executer:
 *      Files :
 *			core/executer/ms_executer.c
 *			core/executer/ms_processes.c
 *			core/executer/ms_redirections.c
*/

void		ms_add_redir(t_process *proc, t_token_type type, char *filepath);
void		ms_executer(t_minishell *ms);
void		ms_build_redir(t_minishell *ms, t_token *token, t_process *process);
void		ms_build_processes(t_minishell *ms);
void		ms_start_processes(t_minishell *ms);
bool		ms_is_redirection(t_token *tok);

/*
 *  Utils processes:
 *      Files :
 *			core/utils/ms_utils_processes.c
 *			core/utils/ms_utils_pipe.c
*/

void		ms_build_type_lines(t_minishell *ms);
void		dup_pipe(t_process *proc);
void		close_pipe(t_process *proc);
void		init_pipe(t_process *proc);

/*
 *	Memory:
 *		files :	
 *			core/utils/ms_utils_free.c
*/

int			ms_free_before_exit(t_minishell *ms);
void		ms_free_last_command(t_minishell *ms);
void		ms_free_all_tokens(t_minishell *ms);
void		ms_free_all_redirections(t_process *process);
void		ms_free_env(t_minishell *ms);

#endif
