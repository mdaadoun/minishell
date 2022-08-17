/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:15:26 by dlaidet           #+#    #+#             */
/*   Updated: 2022/08/17 10:46:05 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	get_length(char *string, int start)
{
	int	length;

	length = 0;
	while (string[start] != '\0' && string[start] != '|')
	{
		length++;
		start++;
	}
	return (length);
}

/* 
 *	Replace the given token with new token separated by pipes 
*/
static void	rebuild_pipes_token(t_minishell *ms, t_token *token)
{
	t_token	*tok1;
	t_token	*tok2;
	char	*str;
	int		ind;
	int		sta;

	sta = 0;
	ind = 0;
	str = token->content;
	tok1 = token;
	while (str[ind])
	{
		if (str[ind] == '|')
		{
			if (ind == 0)
				tok1->content = ft_substr(str, sta, get_length(str, sta) + 1);
			else
			{
				tok1->content = ft_substr(str, sta, get_length(str, sta));
				tok2 = ms_create_new_token(ms);
				ms_push_token(tok1, tok2);
				tok1 = tok2;
				sta = sta + get_length(str, sta);
				tok1->content = ft_substr(str, sta, get_length(str, sta) + 1);
				if (!str[ind + 1])
					break ;
			}
			tok2 = ms_create_new_token(ms);
			ms_push_token(tok1, tok2);
			tok1 = tok2;
			sta++;
		}
		ind++;
		if (!str[ind])
			tok1->content = ft_substr(str, sta, get_length(str, sta));
	}
	free(str);
}

/*
 * Parse the pipes which are not already parsed
*/
void	ms_parse_pipes(t_minishell *ms)
{
	t_token	*token;
	size_t	i;

	token = ms->first_token;
	while (token)
	{
		if (token->type != NO_TYPE)
		{
			token = token->next;
			continue ;
		}
		i = 0;
		while (token->content[i] && ft_strlen(token->content) > 1)
		{
			if (token->content[i] == '|')
				rebuild_pipes_token(ms, token);
			i++;
		}
		token = token->next;
	}
}
