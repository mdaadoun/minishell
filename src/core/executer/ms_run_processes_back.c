/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_run_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:05:09 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/18 07:53:31 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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
