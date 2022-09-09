/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_build_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 07:47:41 by dlaidet           #+#    #+#             */
/*   Updated: 2022/09/07 08:30:13 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	add_process(t_process *proc)
{
	t_process	*new_process;

	new_process = (t_process *)ft_calloc(sizeof(t_process), 1);
	new_process->internal_error = (t_error *)ft_calloc(sizeof(t_error), 1);
	proc->next = new_process;
	new_process->prev = proc;
}

static size_t	count_tok(t_token *tok)
{
	size_t	nb;

	nb = 0;
	while (tok && tok->type != TYPE_PIPE)
	{
		if (is_redirect(tok) == 0)
			nb++;
		tok = tok->next;
	}
	return (nb + 1);
}

static t_process	*new_proc(t_minishell *ms, t_process *proc, t_token *tok)
{
	add_process(proc);
	proc = proc->next;
	proc->cmd = (char **)ft_calloc(sizeof(char *), count_tok(tok->next));
	proc->envp = ms->envp;
	return (proc);
}

static void	builder(t_minishell *ms, t_token *tok, t_process *proc)
{
	size_t	ind;

	ind = 0;
	while (tok)
	{
		if (tok->type == TYPE_EXTERNAL_COMMAND)
			proc->exec_path = tok->external_path;
		if (tok->type == TYPE_BUILTIN_COMMAND)
			proc->builtin = tok->builtin;
		ms_build_redir(ms, tok, proc);
		if (tok->type == TYPE_PIPE)
		{
			proc = new_proc(ms, proc, tok);
			ind = 0;
		}
		else if (is_redirect(tok) == 0)
		{
			proc->cmd[ind] = ft_strdup(tok->content);
			ind++;
		}
		else if (is_redirect(tok) != 0)
			tok = tok->next;
		if (tok)
			tok = tok->next;
	}
}

void	ms_build_processes(t_minishell *ms)
{
	t_process	*proc;
	t_token		*tok;

	tok = ms->first_token;
	proc = (t_process *)ft_calloc(sizeof(t_process), 1);
	if (!proc)
	{
		ms_set_error(ms->global_error, ERROR_MALLOC, MSG_ERROR_MALLOC);
		exit(ms_free_before_exit(ms));
	}
	proc->internal_error = (t_error *)ft_calloc(sizeof(t_error), 1);
	proc->cmd = (char **)ft_calloc(sizeof(char *), count_tok(tok));
	proc->envp = ms->envp;
	ms->first_process = proc;
	builder(ms, tok, proc);
	ms_build_type_lines(ms);
}