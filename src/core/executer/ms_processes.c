/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:05:09 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/10 14:13:17 by dlaidet          ###   ########.fr       */
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
 * Create an array of the token type for each process.
*/
static void build_type_line(t_minishell *ms)
{
	t_token_type	*types_line;
	int				nb_tokens;
	int				i;
	t_process 		*process;
    t_token 		*token;

	token = ms->first_token;
	process = ms->first_process;
	while (process)
	{
		nb_tokens = process->nb_tokens;
		types_line = (t_token_type *) ft_calloc(sizeof(t_token_type), nb_tokens);
		if (!process)
		{
			ms_set_error(ms, ERROR_MALLOC, MSG_ERROR_MALLOC);
			exit(ms_free_before_exit(ms));
		}
		i = 0;
		while(i < nb_tokens)
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
	// start by counting processes with pipe, if any pipe raise flag: has_pipe
	// then build each commands from token as a char ** and type as a int * 
 *
*/
void ms_build_processes(t_minishell *ms)
{
	char		*command;
	char		*new_command;
    t_token 	*token;
	t_process 	*process;

	token = ms->first_token;
	ms->nb_processes = 1;
	process = (t_process *)ft_calloc(sizeof(t_process), 1);
	if (!process)
	{
		ms_set_error(ms, ERROR_MALLOC, MSG_ERROR_MALLOC);
		exit(ms_free_before_exit(ms));
	}
	command = (char *)ft_calloc(sizeof(char), 1);
	if (!command)
	{
		ms_set_error(ms, ERROR_MALLOC, MSG_ERROR_MALLOC);
		exit(ms_free_before_exit(ms));
	}
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

// close pipe
static void	ft_close_pipe(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

//child function
static void	ft_child(int in, int out)
{
	dup2(out, 1);
// close 0 or 1 in certain case
	dup2(in, 0);
// build command or check command
// cmd == path + core cmd
// arg == core cmd + arg
// envp == environement variable
	execve(cmd, arg, envp);
}

/*
 * fork and zait
 * 1. launch external
 * 2. or launch builtin
 * 3. or print error
 *
*/
void ms_start_processes(t_minishell *ms)
{
	int	pipe[2];
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == 0)
		//launch child
	pid2 = fork();
	if (pid2 == 0)
		//launch child
	ft_close_pipe(pipe);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
