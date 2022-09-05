/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_run_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:01:33 by dlaidet           #+#    #+#             */
/*   Updated: 2022/09/05 12:28:32 by dlaidet          ###   ########.fr       */
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
		else if (redir->type == TYPE_REDIRECT_DOUBLE_LEFT)
			redir->fd = open(redir->filepath, O_RDONLY);
		redir = redir->next;
	}
}

static bool	is_builtin_fork(t_builtins built)
{
	if (built == BIN_CD)
		return (false);
	if (built == BIN_EXPORT)
		return (false);
	if (built == BIN_UNSET)
		return (false);
	if (built == BIN_EXIT)
		return (false);
	return (true);
}

static void	execv_builtin(t_minishell *ms, t_builtins built, char **arg)
{
	if (built == BIN_ECHO)
		ms_echo(ms, arg);
	else if (built == BIN_CD)
		ms_cd(ms, arg);
	else if (built == BIN_PWD)
		ms_pwd(ms);
	else if (built == BIN_EXPORT)
		ms_export(ms, arg);
	else if (built == BIN_UNSET)
		ms_unset(ms, arg);
	else if (built == BIN_ENV)
		ms_env(ms);
	else if (built == BIN_EXIT)
		ms_exit(ms, arg);
	else if (built == BIN_NULL)
		exit(ms_free_before_exit(ms));
	if (is_builtin_fork(built) == true)
		exit(ms_free_before_exit(ms));
}

static void	set_redir_fd(t_redirection *redir)
{
	while (redir)
	{
		if (redir->type == TYPE_REDIRECT_RIGHT)
			dup2(redir->fd, 1);
		else if (redir->type == TYPE_REDIRECT_LEFT)
			dup2(redir->fd, 0);
		else if (redir->type == TYPE_REDIRECT_DOUBLE_RIGHT)
			dup2(redir->fd, 1);
		else if (redir->type == TYPE_REDIRECT_DOUBLE_LEFT)
			dup2(redir->fd, 0);
		redir = redir->next;
	}
}

static void	exec_external(t_process *proc)
{
	t_redirection	*redir;

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
			set_redir_fd(proc->first_redirection);
		execve(proc->exec_path, proc->cmd, proc->envp);
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
}

static void	exec_builtin(t_minishell *ms, t_process *proc)
{
	t_redirection	*redir;

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
			set_redir_fd(proc->first_redirection);
		execv_builtin(ms, proc->builtin, proc->cmd);
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
}

void	ms_start_processes(t_minishell *ms)
{
	t_redirection	*redir;
	t_process		*proc;
	int				pip[2];
	int				status;

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
		if (proc->types_line[0] == TYPE_EXTERNAL_COMMAND)
			exec_external(proc);
		if (proc->types_line[0] == TYPE_BUILTIN_COMMAND)
		{
			if (is_builtin_fork(proc->builtin) == true)
				exec_builtin(ms, proc);
			else
				execv_builtin(ms, proc->builtin, proc->cmd);
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
		waitpid(proc->pid, &status, 0);
		if (proc->types_line[0] == TYPE_EXTERNAL_COMMAND)
			if (!ms->global_error->flag)
				if (WIFEXITED(status))
					ms->exit_status = WEXITSTATUS(status);
		proc = proc->next;
	}
}
