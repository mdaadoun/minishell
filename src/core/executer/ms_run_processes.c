/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_run_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:01:33 by dlaidet           #+#    #+#             */
/*   Updated: 2022/08/21 09:21:41 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	init_fd_redirection(t_process *proc)
{
	t_redirection	*redir;

	redir = proc->first_redirection;
	while (redir)
	{
		if (redir->type == TYPE_REDIRECT_RIGHT)
			redir->fd = open(redir->filepath, O_WRONLY | O_TRUNC | O_CREAT, 0644);	
		else if (redir->type == TYPE_REDIRECT_LEFT)
			redir->fd = open(redir->filepath, O_RDONLY);
		else if (redir->type == TYPE_REDIRECT_DOUBLE_RIGHT)
			redir->fd = open(redir->filepath, O_WRONLY | O_APPEND | O_CREAT, 0644);
		redir = redir->next;
	}
}

static void	exec_builtin(t_minishell *ms, t_builtins built, char **arg)
{
	if (built == BIN_ECHO)
		ms_echo(arg);
	else if (built == BIN_CD)
		ms_cd(ms, arg);
	else if (built == BIN_PWD)
		ms_pwd();
	else if (built == BIN_EXPORT)
		ms_export(ms, arg);
	else if (built == BIN_UNSET)
		ms_unset(ms, arg);
	else if (built == BIN_ENV)
		ms_env(ms);
	else if (built == BIN_EXIT)
		ms_exit(ms);
	else if (built == BIN_NULL)
		exit(-1);
	exit(0);
}

void	ms_start_processes(t_minishell *ms)
{
	t_process	*proc;
	int			pip[2];
	t_redirection	*redir;

	proc = ms->first_process;
	while (proc)
	{
		proc->pipe_in = 0;
		proc->pipe_out = 1;
		proc = proc->next;
	}
	proc = ms->first_process;
	while (proc)
	{
		if (proc->next)
		{
			pipe(pip);
			proc->pipe_out = pip[1];
			proc->next->pipe_in = pip[0];
		}
		if (proc->has_redirection == true)
			init_fd_redirection(proc);
		proc->pid = fork();
		if (proc->pid == 0)
		{
			dup2(proc->pipe_in, 0);
			if (proc->pipe_in != 0)
				close(proc->prev->pipe_out);
			dup2(proc->pipe_out, 1);
			if (proc->pipe_out != 1)
				close(proc->next->pipe_in);
			if (proc->has_redirection == true)
			{
				redir = proc->first_redirection;
				while (redir)
				{
					if (redir->type == TYPE_REDIRECT_RIGHT)
						dup2(redir->fd, 1);
					else if (redir->type == TYPE_REDIRECT_LEFT)
						dup2(redir->fd, 0);
					else if (redir->type == TYPE_REDIRECT_DOUBLE_RIGHT)
						dup2(redir->fd, 1);
					redir = redir->next;
				}
			}
			if (proc->types_line[0] == TYPE_EXTERNAL_COMMAND)
				execve(proc->exec_path, proc->cmd, proc->envp);
			else if (proc->types_line[0] == TYPE_BUILTIN_COMMAND)
				exec_builtin(ms, proc->builtin, proc->cmd);
		}
		if (proc->pipe_in != 0)
			close(proc->pipe_in);
		if (proc->pipe_out != 1)
			close(proc->pipe_out);
		if (proc->has_redirection == true)
		{
			redir = proc->first_redirection;
			while (redir)
			{
				close(redir->fd);
				redir = redir->next;
			}
		}
		proc = proc->next;
	}
	proc = ms->first_process;
	while (proc)
	{
		waitpid(proc->pid, NULL, 0);
		proc = proc->next;
	}
}
