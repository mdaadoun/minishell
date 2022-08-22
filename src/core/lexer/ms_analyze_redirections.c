/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_analyze_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:07:36 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/22 11:51:07 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void set_redirect_type(t_token *token, t_token_type type)
{
	token->type = type;
	if (token->next)
		token->next->type = TYPE_ARG_REDIRECT;
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
			set_redirect_type(token, TYPE_REDIRECT_LEFT);
		else if (!ft_strncmp(">", token->content, len))
			set_redirect_type(token, TYPE_REDIRECT_RIGHT);
		else if (!ft_strncmp("<<", token->content, len))
			set_redirect_type(token, TYPE_REDIRECT_DOUBLE_LEFT);
		else if (!ft_strncmp(">>", token->content, len))
			set_redirect_type(token, TYPE_REDIRECT_DOUBLE_RIGHT);
		token = token->next;
	}
}
