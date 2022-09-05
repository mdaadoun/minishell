/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:06:55 by dlaidet           #+#    #+#             */
/*   Updated: 2022/09/05 14:09:41 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	init_fd_redirection(t_process *proc)
{
	t_redirection	*red;

	red = proc->first_redirection;
	while (red)
	{
		if (red->type == TYPE_REDIRECT_RIGHT)
			red->fd = open(red->filepath, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (red->type == TYPE_REDIRECT_LEFT)
			red->fd = open(red->filepath, O_RDONLY);
		else if (red->type == TYPE_REDIRECT_DOUBLE_RIGHT)
			red->fd = open(red->filepath, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (red->type == TYPE_REDIRECT_DOUBLE_LEFT)
			red->fd = open(red->filepath, O_RDONLY);
		red = red->next;
	}
}

void	set_redir_fd(t_redirection *redir)
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
