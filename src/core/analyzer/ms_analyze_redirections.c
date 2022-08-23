/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_analyze_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:07:36 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/23 16:19:23 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

bool	ms_is_redirection(t_token *tok)
{
	if (tok->type == TYPE_REDIRECT_DOUBLE_LEFT || \
		tok->type == TYPE_REDIRECT_LEFT || \
		tok->type == TYPE_REDIRECT_DOUBLE_RIGHT || \
		tok->type == TYPE_REDIRECT_RIGHT )
		return (true);
	return (false);
}

static void set_redirect_type(t_minishell *ms, t_token *tok, t_token_type type)
{
	tok->type = type;
	if (tok->next)
	{
		if (type == TYPE_REDIRECT_DOUBLE_LEFT)
			tok->next->type = TYPE_ARG_DELIMITER;
		else
			tok->next->type = TYPE_ARG_REDIRECT_FILE;
		if (tok->next->next)
			ms_analyze_command(ms, tok->next->next);
	}
}

// Give type for each token with a redirection
void	ms_analyze_redirections(t_minishell *ms)
{
	t_token	*token;
	size_t	len;

	token = ms->first_token;
	while (token)
	{
		len = ft_strlen(token->content);
		if (!ft_strncmp("<", token->content, len))
			set_redirect_type(ms, token, TYPE_REDIRECT_LEFT);
		else if (!ft_strncmp(">", token->content, len))
			set_redirect_type(ms, token, TYPE_REDIRECT_RIGHT);
		else if (!ft_strncmp("<<", token->content, len))
			set_redirect_type(ms, token, TYPE_REDIRECT_DOUBLE_LEFT);
		else if (!ft_strncmp(">>", token->content, len))
			set_redirect_type(ms, token, TYPE_REDIRECT_DOUBLE_RIGHT);
		token = token->next;
	}
}
