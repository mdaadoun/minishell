/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_run_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:01:33 by dlaidet           #+#    #+#             */
/*   Updated: 2022/09/12 14:35:57 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	execv_builtin(t_minishell *ms, t_builtins built, char **arg)
{
	if (built == BIN_ECHO)
		ms_echo(arg);
	else if (built == BIN_CD)
		ms_cd(ms, arg);
	else if (built == BIN_PWD)
		ms_pwd(ms, arg);
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

static void	exec_child(t_minishell *ms, t_process *proc, bool flag)
{
	if (flag == false && is_builtin_fork(proc->builtin) == false)
		execv_builtin(ms, proc->builtin, proc->cmd);
	else
	{
		proc->pid = fork();
		if (proc->pid == 0)
		{
			dup_pipe(proc);
			if (flag == true)
				execve(proc->exec_path, proc->cmd, proc->envp);
			else
				execv_builtin(ms, proc->builtin, proc->cmd);
		}
	}
}

static void	wait_proc(t_minishell *ms, t_process *proc)
{
	int		status;

	while (proc)
	{
		waitpid(proc->pid, &status, 0);
		if (proc->types_line[0] == TYPE_EXTERNAL_COMMAND || \
			is_builtin_fork(proc->builtin))
			if (!ms->global_error->flag)
				if (WIFEXITED(status))
					g_sig.exit_status = WEXITSTATUS(status);
		proc = proc->next;
	}
}

void	ms_start_processes(t_minishell *ms)
{
	t_process		*proc;
	int				pip[2];

	proc = ms->first_process;
	init_pipe(proc);
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
			exec_child(ms, proc, true);
		if (proc->types_line[0] == TYPE_BUILTIN_COMMAND)
			exec_child(ms, proc, false);
		close_pipe(proc);
		proc = proc->next;
	}
	wait_proc(ms, ms->first_process);
}
