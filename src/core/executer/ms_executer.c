/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:46:11 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/08 11:44:47 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"


/*
 *  build each commands from tokens
 *
*/
void build_processes(t_minishell *ms)
{
    (void) ms;
}

// fork and wait
void start_processes(t_minishell *ms)
{
    (void) ms;
}

void ms_executer(t_minishell *ms)
{
    if (checking_no_errors(ms))
    {
        build_processes(ms);
        start_processes(ms);
    }
}
