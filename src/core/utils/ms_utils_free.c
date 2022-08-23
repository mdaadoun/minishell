/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:48:48 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/23 15:20:12 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
 *	Free memory related to the last command.
 *	Reset processes data to start anew
 *	Free all processes
 * 		delete .heredoc file if present
 */
void	ms_free_last_command(t_minishell *ms)
{
	t_process	*process;
	t_process	*swp;
	int			idx;

	if (ms)
	{
		process = ms->first_process;
		while (process)
		{
			swp = process->next;
			idx = 0;
			while (process->cmd[idx])
				free(process->cmd[idx++]);
			free(process->cmd);
			free(process->types_line);
			free(process->internal_error);
			if (process->has_redirection)
				ms_free_all_redirections(process);
			unlink(".heredoc");
			free(process);
			process = swp;
		}
		ms->first_process = NULL;
		if (ms->full_command)
			free(ms->full_command);
		ms->full_command = NULL;
		ms_free_all_tokens(ms);
	}
}

/*
 *	Free all the process allocated memory and print error message if any.
 *
 *	@params:
 *		ms : the main minishell data structure to free.
 *	@return:
 *		EXIT_SUCCESS or EXIT_FAILURE depending error.
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
		ms_free_env(ms);
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
 *	Free all variables from the local copied environment.
*/
void	ms_free_env(t_minishell *ms)
{
	t_variable *variable;
	t_variable *tmp;

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
