/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:46:11 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/09 12:02:16 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
 *  For each execution:
 *      1. Build from tokens all the commands separated from pipes
 *      2. Check each command and find out errors 
 *      3. If no error, start the processes from each command
 *      4. Free the processes.
*/
void ms_executer(t_minishell *ms)
{
    ms_build_processes(ms);
    ms_checking_for_errors(ms);
    if (!ms->error)
        ms_start_processes(ms);
    else
        perror(strerror(ms->error));
    ms_free_all_processes(ms);
}
