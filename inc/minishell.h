/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:06:13 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/01 15:14:42 by mdaadoun         ###   ########.fr       */
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

/*
 *	Elements:
 *		name:	shell name.
 *		path:	the current working directory.
 *		line:	last line read from input.
*/
typedef struct e_minishell {
	char	*name;
	char	**path;
	char	*line;
}           t_minishell;


/*
 *  Errors structures:
*/

# define MSG_ERROR_PARAMS "Minishell don't take any parameter."
# define MSG_ERROR_ALLOC "An error with memory allocation occured."
# define MSG_ERROR_UNKNOWN "Error."

typedef enum e_error {
    SUCCESS,
    ERROR_PARAMS,
    ERROR_ALLOC,
    ERROR_TMP_3,
    ERROR_TMP_4,
    ERROR_UNKNOWN
}           t_error;

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
t_uint8 ms_echo(char **args, char option);
t_uint8 ms_cd(char **args);
t_uint8 ms_pwd(char **args);
t_uint8 ms_export(char **args);
t_uint8 ms_unset(char **args);
t_uint8 ms_env(char **args);
t_uint8 ms_exit(void);

/*
 *  Signal handling:
*/


/*
 *	Errors and memory:
 *		files :	
 *			core/parser/ms_errors.c
 *			core/executor/ms_free.c
*/

int    ms_free_before_exit(t_minishell *ms, int err_key);


/*
 *  Debug variables and functions:
 *		files :	
 *			test/test_builtin.c
 *			test/test_main.c
*/

#ifndef DEBUG
# define DEBUG 0
#endif

void  run_test(int argc, char **argv, char **envp);
void  test_builtin(int argc, char **argv, char **envp);

#endif
