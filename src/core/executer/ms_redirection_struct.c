/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:00:13 by dlaidet           #+#    #+#             */
/*   Updated: 2022/08/18 13:40:54 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static t_redirection	*create_redirection(void)
{
	t_redirection	*redir;

	redir = ft_calloc(sizeof(t_redirection), 1);
	if (!redir)
		return (0);
	return (redir);
}

static void	append_redirection(t_redirection *first, t_redirection *last)
{
	t_redirection	*tmp;

	tmp = first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = last;
}

t_redirection	*ms_add_redirection(t_process *proc, t_token_type type)
{
	t_redirection	*redir;

	redir = create_redirection();
	redir->type = type;
	if (!proc->first_redirection)
		proc->first_redirection = redir;
	else
		append_redirection(proc->first_redirection, redir);
	return (redir);
}
