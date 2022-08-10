/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:37:03 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/10 13:40:57 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	// For each token, if 2 pipe next to each other, pipe error
	// IF command builtin echo and option is not n OR if there is an option ERROR OPTION
	// FOR EACH builtin, check if arguments are valid, exemple for echo, one argument, one equal sign
	(void) ms;
	ft_printf("checking errors\n");
}

// set the error to the shell.
void ms_set_error(t_minishell *ms, t_err_key err_key, char *err_msg)
{
	// if (err_key)
	// {
		ms->error->flag = true;
		ms->error->msg = err_msg;
		ms->error->length = ft_strlen(err_msg);
		ms->error->key = err_key;
	// }
	// else
	// {
	// 	ms->error->flag = false;
	// 	ms->error->msg = NULL;
	// 	ms->error->length = 0;
	// 	ms->error->key = err_key;
	// }
}