/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:57:46 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/23 12:22:07 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	get_length(char *string, int start)
{
	int	length;

	length = 0;
	if (string[start] == '<' && string[start + 1] == '<')
		length++;
	if (string[start] == '>' && string[start + 1] == '>')
		length++;
	while (string[start] != '\0' && \
			string[start] != '<' && string[start] != '>')
	{
		length++;
		start++;
	}
	return (length);
}

static void	rebuild_redirection_tokens(t_minishell *ms, t_token *token)
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
		if (str[ind] == '<' || str[ind] == '>')
		{
			if (ind == 0)
				tok1->content = ft_substr(str, sta, get_length(str, sta) + 1);
			else
			{
				tok1->content = ft_substr(str, sta, get_length(str, sta) + 1);
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
		if ((str[ind] == '>' && str[ind + 1] == '>') || \
				(str[ind] == '<' && str[ind + 1] == '<'))
		{
			ind += 2;
			sta++;
		}
		else
			ind++;
		if (!str[ind])
			tok1->content = ft_substr(str, sta, get_length(str, sta) + 1);
	}
	free(str);
}

/*
 *	Review all token and find out if there is redirections operators (< << >> >)
 *		Ignore tokens that are already tagged SINGLE or DOUBLE quote
 */
void	ms_parse_redirections(t_minishell *ms)
{
	t_token	*tok;
	size_t	i;

	tok = ms->first_token;
	while (tok)
	{
		if (tok->type == TYPE_S_QUOTE_STRING || \
			tok->type == TYPE_D_QUOTE_STRING)
		{
			tok = tok->next;
			continue ;
		}
		i = 0;
		while (tok->content[i] && ft_strlen(tok->content) > 1)
		{
			if (ft_strlen(tok->content) == 2)
				if ((tok->content[i] == '>' && tok->content[i + 1] == '>') \
					|| (tok->content[i] == '<' && tok->content[i + 1] == '<'))
					break ;
			if (tok->content[i] == '>' || tok->content[i] == '<')
				rebuild_redirection_tokens(ms, tok);
			i++;
		}
		tok = tok->next;
	}
}
