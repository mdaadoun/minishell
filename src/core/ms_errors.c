/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:37:03 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/11 09:39:15 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


static void check_bad_commands(t_minishell *ms)
{
	t_process *process;

	process = ms->first_process;
	while (process)
	{
		if (process->types_line[0] != TYPE_EXTERNAL_COMMAND && \
		process->types_line[0] != TYPE_BUILTIN_COMMAND)
			ms_set_error(process->error, ERROR_COMMAND, MSG_ERROR_COMMAND);
	}
}

/*
 *	From token type, find:
 *		1. if command exist (if NO_TYPE instead of BUILTIN or EXTERNAL)
			Check each command and find out errors If valid syntax, checking errors and ignore if not
 * 		2. if syntax correct (pipes next to each other)
 * 		3. redirection error ??
*/
void ms_checking_for_errors(t_minishell *ms)
{
	// For each token, if any BAD_COMMAND, command error
	check_bad_commands(ms);
	// For each token, if 2 pipe next to each other, pipe error
	// IF command builtin echo and option is not n OR if there is an option ERROR OPTION
	// FOR EACH builtin, check if arguments are valid, exemple for echo, one argument, one equal sign
}

// set the error to the shell.
void ms_set_error(t_error *error, t_err_key err_key, char *err_msg)
{
	// if (err_key)
	// {
		error->flag = true;
		error->msg = err_msg;
		error->length = ft_strlen(err_msg);
		error->key = err_key;
	// }
	// else
	// {
	// 	error->flag = false;
	// 	error->msg = NULL;
	// 	error->length = 0;
	// 	error->key = err_key;
	// }
}