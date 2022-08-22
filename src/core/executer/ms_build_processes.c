/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_build_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 07:47:41 by dlaidet           #+#    #+#             */
/*   Updated: 2022/08/22 11:18:44 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	add_process(t_process *proc)
{
	t_process	*new_process;

	new_process = (t_process *)ft_calloc(sizeof(t_process), 1);
	new_process->internal_error = (t_error *)ft_calloc(sizeof(t_error), 1);
	proc->next = new_process;
	new_process->prev = proc;
}

/*
 * Create an array of the token type for each process.
 */
static void	build_type_line(t_minishell *ms)
{
	t_token_type	*types_line;
	int				nb_tokens;
	int				i;
	t_process		*process;
	t_token			*token;

	token = ms->first_token;
	process = ms->first_process;
	while (process)
	{
		nb_tokens = process->nb_tokens;
		types_line = (t_token_type *) ft_calloc(sizeof(t_token_type), nb_tokens);
		if (!process)
		{
			ms_set_error(ms->global_error, ERROR_MALLOC, MSG_ERROR_MALLOC);
			exit(ms_free_before_exit(ms));
		}
		i = 0;
		while (i < nb_tokens)
		{
			types_line[i] = token->type;
			token = token->next;
			i++;
		}
		if (token)
			token = token->next;
		process->types_line = types_line;
		process = process->next;
	}
}

static int	is_redirect(t_token *tok)
{
	if (tok->type == TYPE_REDIRECT_LEFT)
		return (1);
	else if (tok->type == TYPE_REDIRECT_RIGHT)
		return (2);
	else if (tok->type == TYPE_REDIRECT_DOUBLE_RIGHT)
		return (3);
	else if (tok->type == TYPE_REDIRECT_DOUBLE_LEFT)
		return (4);
	return (0);
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

void	ms_build_proc(t_minishell *ms)
{
	t_process	*proc;
	t_token		*tok;
	size_t		ind;

	ind = 0;
	tok = ms->first_token;
	ms->nb_processes = 1;
	proc = (t_process *)ft_calloc(sizeof(t_process), 1);
	if (!proc)
	{
		ms_set_error(ms->global_error, ERROR_MALLOC, MSG_ERROR_MALLOC);
		exit(ms_free_before_exit(ms));
	}
	proc->internal_error = (t_error *)ft_calloc(sizeof(t_error), 1);
	proc->cmd = (char **)ft_calloc(sizeof(char *), count_tok(tok));
	ms->first_process = proc;
	while (tok)
	{
		if (tok->type == TYPE_EXTERNAL_COMMAND)
			proc->exec_path = tok->external_path;
		if (tok->type == TYPE_BUILTIN_COMMAND)
			proc->builtin = tok->builtin;
		ms_build_redirections(tok, proc);
		if (tok->type == TYPE_PIPE)
		{
			if (!ms->has_pipe)
				ms->has_pipe = true;
			add_process(proc);
			proc->envp = ms->envp;
			proc = proc->next;
			proc->cmd = (char **)ft_calloc(sizeof(char *), count_tok(tok->next));
			proc->envp = ms->envp;
			ms->nb_processes++;
			ind = 0;
		}
		else if (is_redirect(tok) == 0)
		{
			proc->cmd[ind] = ft_strdup(tok->content);
			ind++;
			proc->nb_tokens++;
		}
		else if (is_redirect(tok) != 0)
			tok = tok->next;
		tok = tok->next;
	}
	build_type_line(ms);
}
