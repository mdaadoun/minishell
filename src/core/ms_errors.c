/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:37:03 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/09 09:33:31 by mdaadoun         ###   ########.fr       */
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
	(void) ms;
	ft_printf("checking errors\n");
}
