/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 09:03:27 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/05 10:44:56 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// delete all empty token
void	clean_tokens(t_minishell *ms)
{
	t_token	*token;

	token = ms->first_token;
	while (token)
	{
		if (ft_strlen(token->content) == 0)
		{
			if (token == ms->first_token)
			{
				token = ms_delete_token(token);
				ms->first_token = token;
			}
			else
				token = ms_delete_token(token);
		}
		else
			token = token->next;
	}
}

static void	combine_tokens(t_minishell *ms)
{
	t_token	*token;

	token = ms->first_token;
	while (token)
	{
		if (token->no_space && token->next)
			ms_combine_token(token, token->next);
		else
			token = token->next;
	}
}

// build data structure from line 
// read command line and build tokens structure 
// (space "" '' $ |)
void	ms_parser(t_minishell *ms)
{
	ms_parse_quotes(ms, ms->full_command, 0);
	ms_swap_env(ms);
	ms_parse_pipes(ms);
	ms_parse_redirections(ms);
	combine_tokens(ms);
	clean_tokens(ms);
}
