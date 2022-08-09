/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:05:09 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/09 12:01:52 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"


static void add_process(t_process *proc)
{
	t_process *new_process;

	new_process = (t_process *)ft_calloc(sizeof(t_process), 1);
	proc->next = new_process;
}

/*
 *  build each commands from tokens
	// start by counting processes with pipe, if any pipe raise flag: has_pipe
	// then build each commands from token as a char ** and type as a int * 
 *
*/
void ms_build_processes(t_minishell *ms)
{
	char		*command;
    t_token 	*token;
	t_process 	*process;

	token = ms->first_token;
	ms->nb_processes = 1;
	process = (t_process *)ft_calloc(sizeof(t_process), 1);
	if (!process)
		exit(ms_free_before_exit(ms, ENOMEM));
	command = (char *)ft_calloc(sizeof(char), 1);
	if (!command)
		exit(ms_free_before_exit(ms, ENOMEM));
	ms->first_process = process;
	while (token)
	{
		if (token->type == TYPE_PIPE)
		{
			if (!ms->has_pipe)
				ms->has_pipe = true;
			add_process(process);
			process->command_line = command;
			command = (char *)ft_calloc(sizeof(char), 1);
			process = process->next;
			ms->nb_processes++;
		}
		else
		{
			command = ft_strjoin(command, token->content);
			command = ft_strjoin(command, " ");
			process->nb_tokens++;
		}
		token = token->next;
	}
	process->command_line = command;
}

// fork and wait
void ms_start_processes(t_minishell *ms)
{
	(void) ms;
}

void ms_free_all_processes(t_minishell *ms)
{
	t_process 	*process;
    t_process	*swp;

	ms->has_pipe = false;
	ms->nb_processes = 0;
	process = ms->first_process;
	while (process)
	{
        swp = process->next;
        free(process->command_line);
        // free(process->types_line);
        free(process);
        process = swp;
	}
	ms->first_process = NULL;
}
