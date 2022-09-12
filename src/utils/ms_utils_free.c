/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:48:48 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/12 09:32:10 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_process	*free_process(t_process *process)
{
	t_process	*swp;
	int			idx;

	swp = process->next;
	idx = 0;
	while (process->cmd[idx])
	{
		free(process->cmd[idx]);
		idx++;
	}
	free(process->cmd);
	free(process->types_line);
	free(process->internal_error);
	if (process->has_redirection)
		ms_free_all_redirections(process);
	unlink(".heredoc");
	free(process);
	return (swp);
}

/*
 *	Free memory related to the last command.
 *	Reset processes data to start anew
 *	Free all processes
 * 		delete .heredoc file if present
 */
void	ms_free_last_command(t_minishell *ms)
{
	t_process	*process;

	g_sig.in_process = false;
	if (ms)
	{
		process = ms->first_process;
		while (process)
			process = free_process(process);
		ms->first_process = NULL;
		if (ms->full_command)
			free(ms->full_command);
		ms->full_command = NULL;
		ms_free_all_tokens(ms);
	}
}

/*
 *	Free all variables from the local copied environment.
*/
void	ms_free_env(t_minishell *ms)
{
	t_variable	*variable;
	t_variable	*tmp;

	variable = ms->first_var;
	while (variable)
	{
		free(variable->name);
		free(variable->content);
		tmp = variable;
		variable = variable->next;
		free(tmp);
	}
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

/*
 * Free all the redirection structure of the given process.
*/
void	ms_free_all_redirections(t_process *process)
{
	t_redirection	*redirection;
	t_redirection	*swp;

	redirection = process->first_redirection;
	while (redirection)
	{
		swp = redirection->next;
		free(redirection->filepath);
		free(redirection);
		redirection = swp;
	}
	process->first_redirection = NULL;
}
