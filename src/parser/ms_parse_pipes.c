/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:15:26 by dlaidet           #+#    #+#             */
/*   Updated: 2022/09/07 10:08:35 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static void	create_and_push_token(t_minishell *ms, t_token **t1, t_token **t2)
{
	*t2 = ms_create_new_token(ms);
	ms_push_token(*t1, *t2);
	*t1 = *t2;
}

static void	rebuild_pipes_token(t_minishell *ms, t_token *t1, \
t_token *t2, char *str)
{
	int		sta;
	int		ind;

	ind = 0;
	sta = 0;
	while (str[ind])
	{
		if (str[ind] == '|')
		{
			if (ind != 0)
			{
				t1->content = ft_substr(str, sta, get_length(str, sta));
				create_and_push_token(ms, &t1, &t2);
				sta = sta + get_length(str, sta);
			}
			t1->content = ft_substr(str, sta, get_length(str, sta) + 1);
			if (ind != 0 && !str[ind + 1])
				break ;
			create_and_push_token(ms, &t1, &t2);
			sta++;
		}
		ind++;
		if (!str[ind])
			t1->content = ft_substr(str, sta, get_length(str, sta));
	}
}

/* 
 *	Replace the given token with new token separated by pipes 
*/
static void	start_rebuild_pipes_token(t_minishell *ms, t_token *token)
{
	t_token	*tok1;
	t_token	*tok2;
	char	*str;

	str = token->content;
	tok1 = token;
	tok2 = NULL;
	rebuild_pipes_token(ms, tok1, tok2, str);
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
			{
				start_rebuild_pipes_token(ms, token);
				break ;
			}
			i++;
		}
		token = token->next;
	}
}
