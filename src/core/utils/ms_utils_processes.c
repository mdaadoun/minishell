/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:49:41 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/06 10:02:33 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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

/*
 * Create an array of the token type for each process.
 */
void	ms_build_type_lines(t_minishell *ms)
{
	t_token_type	*types_line;
	t_process		*process;
	t_token			*token;
	int8_t			nb_tokens;
	int8_t			idx;

	process = ms->first_process;
	token = ms->first_token;
	while (process)
	{
		nb_tokens = count_tokens(token) + 1;
		types_line = (t_token_type *) ft_calloc(sizeof(int), (size_t)nb_tokens);
		if (!types_line)
		{
			ms_set_error(ms->global_error, ERROR_MALLOC, MSG_ERROR_MALLOC);
			exit(ms_free_before_exit(ms));
		}
		idx = 0;
		while (token && token->type != TYPE_PIPE)
		{		
			if (token->type != TYPE_ARG_DELIMITER && \
			token->type != TYPE_ARG_REDIRECT_FILE && \
			!ms_is_redirection(token))
			{
				types_line[idx] = token->type;
				idx++;
			}
			token = token->next;
		}
		if (token)
			token = token->next;
		process->types_line = types_line;
		process = process->next;
	}
}