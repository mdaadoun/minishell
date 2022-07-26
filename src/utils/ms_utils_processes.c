/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:49:41 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/12 15:28:48 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int8_t	count_tokens(t_token *token)
{
	int8_t	nb;

	nb = 0;
	while (token && token->type != TYPE_PIPE)
	{
		if (token->type != TYPE_ARG_DELIMITER && \
			token->type != TYPE_ARG_REDIRECT_FILE && \
			!ms_is_redirection(token))
			nb++;
		token = token->next;
	}
	return (nb);
}

static bool	check(t_token_type type)
{
	if (type != TYPE_ARG_DELIMITER && type != TYPE_ARG_REDIRECT_FILE)
		return (false);
	return (true);
}

/*
 * Create an array of the token type for each process.
 */
void	ms_build_type_lines(t_minishell *ms)
{
	t_token_type	*types_line;
	t_process		*process;
	t_token			*token;
	int8_t			idx;

	process = ms->first_process;
	token = ms->first_token;
	while (process)
	{
		types_line = ft_calloc(sizeof(int), count_tokens(token) + 1);
		ft_protect_malloc(ms, types_line);
		idx = 0;
		while (token && token->type != TYPE_PIPE)
		{		
			if (!check(token->type) && !ms_is_redirection(token))
				types_line[idx++] = token->type;
			token = token->next;
		}
		if (token)
			token = token->next;
		process->types_line = types_line;
		process = process->next;
	}
}
