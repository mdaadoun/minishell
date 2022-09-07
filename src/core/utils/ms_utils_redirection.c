/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:06:55 by dlaidet           #+#    #+#             */
/*   Updated: 2022/09/07 12:08:29 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

bool	is_double_redirect(t_minishell *ms, char *str, int ind)
{
	char	*err_msg;

	err_msg = MSG_ERROR_SYNTAX_REDIRECT;
	if ((str[ind] == '>' && str[ind + 1] == '>') || \
				(str[ind] == '<' && str[ind + 1] == '<'))
	{
		if (str[ind + 2] == '<' || str[ind + 2] == '>')
		{
			g_sig.exit_status = 2;
			ms_set_error(ms->global_error, ERROR_SYNTAX, err_msg);
		}
		return (true);
	}
	return (false);
}

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
