/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:46:11 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/12 10:10:17 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 *  For each execution:
 *      1. Build from tokens all the commands separated from pipes
 *      2. Check each processes and find out errors 
 *      3. If error and one process, display error and return prompt shell.
 *      4. If no global error, start the processes for each command
 *          Note: Each process could still have internal errors.
 *      5. Free the processes.
 */
void	ms_executer(t_minishell *ms)
{
	g_sig.in_process = true;
	if (!ms->global_error->flag)
		ms_build_processes(ms);
	if (!ms->global_error->flag)
		ms_checking_for_errors(ms);
	if (!ms->global_error->flag && !g_sig.SIGINT_signal)
		ms_start_processes(ms);
	g_sig.SIGINT_signal = false;
}
