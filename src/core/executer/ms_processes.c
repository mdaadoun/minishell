/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:05:09 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/12 07:10:38 by dlaidet          ###   ########.fr       */
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

void	create_pipes(t_minishell *ms)
{
	t_token		*tok;
	t_process	*proc;
	int			nb_pipe;
	int			pipes[2];

	if (!ms->has_pipe)
		return ;
	nb_pipe = 0;
	tok = ms->first_token;
	while (tok)
	{
		if (tok->type == TYPE_PIPE)
			nb_pipe++;
		tok = tok->next;
	}
	proc = ms->first_process;
	while (proc)
	{
		if (nb_pipe != 0)
		{
			nb_pipe--;
			pipe(pipes);
		}
		if (proc == ms->first_process)
		{
			proc->pipe_in = 0;
			proc->pipe_out = pipes[1];
			proc->next->pipe_in = pipes[0];
		}
		else if (proc->next == 0)
		{
			proc->pipe_out = 1;
		}
		else
		{
			proc->pipe_out = pipes[1];
			proc->next->pipe_in = pipes[0];
		}
		proc = proc->next;
	}
}

/*
 *  build each commands from tokens
	// start by counting processes with pipe, if any pipe raise flag: has_pipe
	// then build each commands from token as a char ** and type as a int * 
 *
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
		if (token->type == TYPE_EXTERNAL_COMMAND)
			process->exec_path = token->external_path;
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

// close pipe
// static void	ft_close_pipe(int pipe[2])
// {
// 	close(pipe[0]);
// 	close(pipe[1]);
// }

//child function
// static void	run_external(int in, int out)
// {
// 	dup2(out, 1);
// // close 0 or 1 in certain case
// 	dup2(in, 0);
// // build command or check command
// // cmd == path + core cmd
// // arg == core cmd + arg
// // envp == environement variable
// 	execve(cmd, arg, envp);
// }

static void	run_process(t_process *process)
{
	char	**arg;

	if (process->pipe_out != 1)
	{
		dup2(process->pipe_out, 1);
		if (process->next)
			close(process->next->pipe_in);
	}
	if (process->pipe_in != 0)
	{
		dup2(process->pipe_in, 0);
		if (process->prev)
			close(process->prev->pipe_out);
	}
	if (process->types_line[0] == TYPE_BUILTIN_COMMAND)
	{
		ft_printf("%d,%d\n", process->pipe_out, process->next->pipe_in);
		ft_printf("run builtin\n");
	}
	else if (process->types_line[0] == TYPE_EXTERNAL_COMMAND)
	{
		arg = ft_split(process->command_line, ' ');
		execve(process->exec_path, arg, process->envp);
	}
	exit(EXIT_SUCCESS);
}

static bool	check_global_error(t_minishell *ms)
{
	if (ms->global_error->flag)
	{
		write(2, ms->global_error->msg, ms->global_error->length);
		write(2, "\n", 1);
		return (false);
	}
	return (true);
}

static void	close_pipe(t_minishell *ms)
{
	t_process	*proc;

	proc = ms->first_process;
	while (proc)
	{
		if (proc->prev)
			close(proc->pipe_in);
		if (proc->next)
			close(proc->pipe_out);
		proc = proc->next;
	}
}

/*
 * fork and wait
 * 1. launch external
 * 2. or launch builtin
 * 3. or print error
 *
*/
void	ms_start_processes(t_minishell *ms)
{
	bool		run_pipeline;
	t_process	*process;

	process = ms->first_process;
	create_pipes(ms);
	run_pipeline = true;
	while (process && run_pipeline)
	{
		process->pid = fork();
		if (process->pid == 0)
		{
			run_pipeline = check_global_error(ms);
			if (run_pipeline)
				run_process(process);
			else
				exit(EXIT_FAILURE);
		}
		process = process->next;
	}
	close_pipe(ms);
	process = ms->first_process;
	while (process)
	{
		waitpid(process->pid, NULL, 0);
		process = process->next;
	}
}
