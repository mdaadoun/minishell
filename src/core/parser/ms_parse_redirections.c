/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:57:46 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/07 12:54:24 by mdaadoun         ###   ########.fr       */
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

static void	create_and_push_redir(t_minishell *ms, t_token **t1)
{
	t_token	*t2;

	t2 = ms_create_new_token(ms);
	ms_push_token(*t1, t2);
	*t1 = t2;
}

void	triple(t_minishell *ms, t_token *tok1, char **str, int sta)
{
	create_and_push_redir(ms, &tok1);
	sta = sta + get_length(*str, sta);
	tok1->content = ft_substr(*str, sta, get_length(*str, sta) + 1);
}

void	test(t_minishell *ms, t_token *tok1, char **str, int sta)
{
	int	ind;

	ind = 0;
	while ((*str)[ind])
	{
		if ((*str)[ind] == '<' || (*str)[ind] == '>')
		{
			tok1->content = ft_substr(*str, sta, get_length(*str, sta));
			if (ind != 0)
			{
				triple(ms, tok1, str, sta);
				if (!(*str)[ind + 1])
					break ;
			}
			create_and_push_redir(ms, &tok1);
			sta++;
		}
		if (is_double_redirect(ms, *str, ind++))
		{
			ind++;
			sta++;
		}
		if (!(*str)[ind])
			tok1->content = ft_substr(*str, sta, get_length(*str, sta) + 1);
	}
}

static void	rebuild_redirection_tokens(t_minishell *ms, t_token *token)
{
	t_token	*tok1;
	char	*str;
	int		sta;

	sta = 0;
	str = token->content;
	tok1 = token;
	test(ms, tok1, &str, sta);
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
