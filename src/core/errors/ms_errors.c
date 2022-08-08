/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:37:03 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/08 17:24:47 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
 *	From token type, find:
 *		1. if command exist (if NO_TYPE instead of BUILTIN or EXTERNAL)
 * 		2. if syntax correct (pipes next to each other)
 * 		3. redirection error ??
*/
void ms_checking_for_errors(t_minishell *ms)
{
	(void) ms;
	ft_printf("checking errors\n");
}
