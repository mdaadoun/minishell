/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_analyzer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 09:04:20 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/06 10:30:59 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
 * analyze each token following this order and set types:
 *      1. Tag the redirections types.
 *      2. Tag all Pipes
 *      	* and check if next token is external or builtin programs
 *		3. Check if first token is a valid command.
 *      4. Check last NO_TYPE if string arg or option.
 */
void	ms_analyzer(t_minishell *ms)
{
	ms_analyze_redirections(ms);
	ms_analyze_pipes(ms);
	if (!ms->global_error->flag)
	{
		ms_analyze_command(ms, ms->first_token);
		ms_analyze_arguments(ms);
	}
}
