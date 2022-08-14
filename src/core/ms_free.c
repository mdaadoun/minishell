/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:48:48 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/14 08:38:38 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Free memory related to the last command.
 */
void	ms_free_last_command(t_minishell *ms)
{
	if (ms)
	{
		if (ms->full_command)
			free(ms->full_command);
		ms_free_all_tokens(ms);
	}
}

/*
 *  Free all the process allocated memory and print error message.
 *  
 * @params:
 *      ms      :   the main minishell data structure to free.
 *      err_key :   the error number to get the correct err msg.
 * @return:
 *      EXIT_SUCCESS or EXIT_FAILURE depending error.
 */
int	ms_free_before_exit(t_minishell *ms)
{
	int	i;

	i = 0;
	if (ms)
	{
		if (ms->cwd_path)
			free(ms->cwd_path);
		if (ms->bin_paths)
		{
			while (ms->bin_paths[i])
				free(ms->bin_paths[i++]);
			free(ms->bin_paths);
		}
		ms_free_last_command(ms);
		ms_free_all_processes(ms);
		if (ms->global_error->flag)
		{
			write(2, ms->global_error->msg, ms->global_error->length);
			write(2, "\n", 1);
			free(ms);
			return (EXIT_FAILURE);
		}
		free(ms);
	}
	return (EXIT_SUCCESS);
}

/*
 * Free all the tokens of the ms structure.
 */
void	ms_free_all_tokens(t_minishell *ms)
{
	t_token	*token;
	t_token	*swp;

	token = ms->first_token;
	while (token)
	{
		swp = token->next;
		free(token->content);
		if (token->external_path)
			free(token->external_path);
		free(token);
		token = swp;
	}
	ms->first_token = NULL;
}

void	ms_free_all_processes(t_minishell *ms)
{
	t_process	*process;
	t_process	*swp;

	ms->has_pipe = false;
	ms->nb_processes = 0;
	process = ms->first_process;
	while (process)
	{
		swp = process->next;
		free(process->command_line);
		free(process->types_line);
		free(process->internal_error);
		free(process);
		process = swp;
	}
	ms->first_process = NULL;
}
