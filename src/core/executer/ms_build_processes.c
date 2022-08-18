/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_build_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 07:47:41 by dlaidet           #+#    #+#             */
/*   Updated: 2022/08/18 07:53:04 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	add_process(t_process *proc)
{
	t_process	*new_process;

	new_process = (t_process *)ft_calloc(sizeof(t_process), 1);
	new_process->internal_error = (t_error *)ft_calloc(sizeof(t_error), 1);
	proc->next = new_process;
	new_process->prev = proc;
}

/*
 * Create an array of the token type for each process.
 */
static void	build_type_line(t_minishell *ms)
{
	t_token_type	*types_line;
	int				nb_tokens;
	int				i;
	t_process		*process;
	t_token			*token;

	token = ms->first_token;
	process = ms->first_process;
	while (process)
	{
		nb_tokens = process->nb_tokens;
		types_line = (t_token_type *) ft_calloc(sizeof(t_token_type), nb_tokens);
		if (!process)
		{
			ms_set_error(ms->global_error, ERROR_MALLOC, MSG_ERROR_MALLOC);
			exit(ms_free_before_exit(ms));
		}
		i = 0;
		while (i < nb_tokens)
		{
			types_line[i] = token->type;
			if (token->type == TYPE_ARG_OPTION && ft_strlen(token->content) == 2)
				process->option = token->content[1];
			token = token->next;
			i++;
		}
		if (token)
			token = token->next;
		process->types_line = types_line;
		process = process->next;
	}
}

/*
 *  build each commands from tokens
 * start by counting processes with pipe, if any pipe raise flag: has_pipe
 * then build each commands from token as a char ** and type as a int * 
 */
void	ms_build_processes(t_minishell *ms)
{
	char		*command;
	char		*new_command;
	t_token		*token;
	t_process	*process;

	token = ms->first_token;
	ms->nb_processes = 1;
	process = (t_process *)ft_calloc(sizeof(t_process), 1);
	process->internal_error = (t_error *)ft_calloc(sizeof(t_error), 1);
	if (!process)
	{
		ms_set_error(ms->global_error, ERROR_MALLOC, MSG_ERROR_MALLOC);
		exit(ms_free_before_exit(ms));
	}
	command = (char *)ft_calloc(sizeof(char), 1);
	if (!command)
	{
		ms_set_error(ms->global_error, ERROR_MALLOC, MSG_ERROR_MALLOC);
		exit(ms_free_before_exit(ms));
	}
	ms->first_process = process;
	while (token)
	{
		ms_build_redirections(token, process);
		if (token->type == TYPE_EXTERNAL_COMMAND)
			process->exec_path = token->external_path;
		if (token->type == TYPE_BUILTIN_COMMAND)
			process->builtin = token->builtin;
		if (token->type == TYPE_PIPE)
		{
			if (!ms->has_pipe)
				ms->has_pipe = true;
			add_process(process);
			process->command_line = command;
			command = (char *)ft_calloc(sizeof(char), 1);
			process->envp = ms->envp;
			process = process->next;
			ms->nb_processes++;
		}
		else
		{
			new_command = ft_strjoin(command, token->content);
			free(command);
			command = new_command;
			new_command = ft_strjoin(command, " ");
			free(command);
			command = new_command;
			process->nb_tokens++;
		}
		token = token->next;
	}
	process->command_line = command;
	build_type_line(ms);
}
