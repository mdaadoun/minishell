/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:05:09 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/17 15:41:10 by mdaadoun         ###   ########.fr       */
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
		if (nb_pipe-- > 0)
			pipe(pipes);
		if (proc == ms->first_process)
		{
			proc->pipe_in = 0;
			proc->pipe_out = pipes[1];
			proc->next->pipe_in = pipes[0];
		}
		else if (proc->next == 0)
			proc->pipe_out = 1;
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

static bool	is_builtin_fork(t_process *proc)
{
	if (proc->builtin == BIN_ECHO)
		return (true);
	if (proc->builtin == BIN_PWD)
		return (true);
	if (proc->builtin == BIN_ENV)
		return (true);
	if (proc->builtin == BIN_CD)
		return (false);
	if (proc->builtin == BIN_EXPORT)
		return (false);
	if (proc->builtin == BIN_UNSET)
		return (false);
	if (proc->builtin == BIN_EXIT)
		return (false);
	return (false);
}

static void	execv_builtin(t_minishell *ms, t_process *proc, bool fork)
{
	if (fork)
	{
		if (proc->builtin == BIN_ECHO)
			ms_echo(proc->command_line);
		if (proc->builtin == BIN_PWD)
			ms_pwd();
		if (proc->builtin == BIN_ENV)
			ms_env(ms);
	}
	else
	{
		if (proc->builtin == BIN_CD)
			ms_cd(ms, proc->command_line);
		if (proc->builtin == BIN_EXPORT)
			ms_export(ms, proc->command_line);
		if (proc->builtin == BIN_UNSET)
			ms_unset(ms, proc->command_line);
		if (proc->builtin == BIN_EXIT)
			ms_exit(ms);
	}
}

static void	run_process_fork(t_minishell *ms, t_process *process)
{
	char	**arg;

	dup2(process->pipe_in, 0);
	if (process->prev)
		close(process->prev->pipe_out);
	dup2(process->pipe_out, 1);
	if (process->next)
		close(process->next->pipe_in);
	if (process->types_line[0] == TYPE_BUILTIN_COMMAND)
	{
		execv_builtin(ms, process, true);
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

static bool	is_fork(t_process *proc)
{
	if (proc->types_line[0] == TYPE_EXTERNAL_COMMAND)
		proc->pid = fork();
	else if (proc->types_line[0] == TYPE_BUILTIN_COMMAND)
	{
		if (is_builtin_fork(proc))
			proc->pid = fork();
		else
			return (false);
	}
	return (true);
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
		if (is_fork(process))
		{
			if (process->pid == 0)
			{
				run_pipeline = check_global_error(ms);
				if (run_pipeline)
				{
					run_process_fork(ms, process);
				}
				else
					exit(EXIT_FAILURE);
			}
		}
		else
		{
			run_pipeline = check_global_error(ms);
			if (run_pipeline)
			{
				execv_builtin(ms, process, false);
				process->pid = fork();
				if (process->pid == 0)
					exit (EXIT_SUCCESS);
			}
			else
			{
				process->pid = fork();
				if (process->pid == 0)
					exit(EXIT_FAILURE);
			}
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
