/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 09:03:27 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/04 13:52:25 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// delete all empty token
void clean_tokens(t_minishell *ms)
{
	t_token *token;

	token = ms->first_token;
	while (token)
	{
		if (ft_strlen(token->content) == 0)
		{
			if (token == ms->first_token)
				ms->first_token = token->next;
			if (token->next)
			{
				token = token->next;
				ms_delete_token(token->prev);
			}
			else
				ms_delete_token(token);
		}
		else
			token = token->next;
	}
}

 // build data structure from line 
 // read command line and build tokens structure 
 // (space "" '' $ |)
void ms_parser(t_minishell *ms)
{
	ms_parse_quotes(ms);
	ms_swap_env(ms);
	ms_parse_pipe(ms);
	clean_tokens(ms);
}
