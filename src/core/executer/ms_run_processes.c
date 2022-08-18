/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_run_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:01:33 by dlaidet           #+#    #+#             */
/*   Updated: 2022/08/18 14:48:19 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	free_arg(char **arg)
{
	int	ind;

	ind = 0;
	while (arg[ind])
	{
		free(arg[ind]);
		ind++;
	}
	free(arg);
}

static void	init_fd_redirection(t_process *proc)
{
	t_redirection	*redir;

	redir = proc->first_redirection;
	while (redir)
	{
		if (redir->type == TYPE_REDIRECT_RIGHT)
		{
		redir->fd = open(redir->filepath, O_WRONLY | O_TRUNC | O_CREAT, 0644);	
		}
		else if (redir->type == TYPE_REDIRECT_LEFT)
		{
			redir->fd = open(redir->filepath, O_RDONLY);
		}
		redir = redir->next;
	}
}

void	ms_start_processes(t_minishell *ms)
{
	t_process	*proc;
	int			pip[2];
	char		**arg;
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
		arg = ft_split(proc->command_line, ' ');
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
					{
						dup2(redir->fd, 1);
					}
					if (redir->type == TYPE_REDIRECT_LEFT)
					{
						dup2(redir->fd, 0);
					}
					redir = redir->next;
				}
			}
			ft_printf("%s\n", proc->command_line);
			if (proc->types_line[0] == TYPE_EXTERNAL_COMMAND)
				execve(proc->exec_path, arg, proc->envp);
			else if (proc->types_line[0] == TYPE_BUILTIN_COMMAND)
			{
				ft_printf("Builtin Command\n");
			}
		}
		if (!arg)
			free_arg(arg);
		if (proc->pipe_in != 0)
			close(proc->pipe_in);
		if (proc->pipe_out != 1)
			close(proc->pipe_out);
		proc = proc->next;
	}
	proc = ms->first_process;
	while (proc)
	{
		waitpid(proc->pid, NULL, 0);
		proc = proc->next;
	}
}
