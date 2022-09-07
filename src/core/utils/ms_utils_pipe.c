/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 08:00:55 by dlaidet           #+#    #+#             */
/*   Updated: 2022/09/07 08:25:13 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	dup_pipe(t_process *proc)
{
	dup2(proc->pipe_in, 0);
	if (proc->pipe_in != 0)
		close(proc->prev->pipe_out);
	dup2(proc->pipe_out, 1);
	if (proc->pipe_out != 1)
		close(proc->next->pipe_in);
	if (proc->has_redirection == true)
		set_redir_fd(proc->first_redirection);
}

void	close_pipe(t_process *proc)
{
	t_redirection	*redir;

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

void	init_pipe(t_process *proc)
{
	while (proc)
	{
		proc->pipe_in = 0;
		proc->pipe_out = 1;
		proc = proc->next;
	}
}
