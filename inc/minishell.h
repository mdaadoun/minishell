/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:06:13 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/07/29 08:34:29 by mdaadoun         ###   ########.fr       */
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


# define NB_ERRORS 5

typedef enum e_errors {
    KEY_ERROR_PARAMS,
    KEY_ERROR_2,
    KEY_ERROR_3,
    KEY_ERROR_4,
    KEY_ERROR_5
}           t_error_key;

typedef struct s_error {
    int     err_key;
    char    *err_msg;
}           t_error;

/*
  builtin shell commands:
*/
t_uint8 ms_echo(char option, char **args);
t_uint8 ms_cd(char **args);
t_uint8 ms_pwd(char **args);
t_uint8 ms_export(char **args);
t_uint8 ms_unset(char **args);
t_uint8 ms_env(void);
t_uint8 ms_exit(void);


# define MSG_ERROR_PARAMS "Minishell don't take any params."

#endif
