/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:15:26 by dlaidet           #+#    #+#             */
/*   Updated: 2022/08/17 10:23:57 by dlaidet          ###   ########.fr       */
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
	t_token	*first_token;
	t_token	*second_token;
	char	*string;
	int		index;
	int		start;

	start = 0;
	index = 0;
	string = token->content;
	first_token = token;
	while (string[index])
	{
		if (string[index] == '|')
		{
			if (index == 0)
				first_token->content = ft_substr(string, start, get_length(string, start) + 1);
			else
			{
				first_token->content = ft_substr(string, start, get_length(string, start));
				second_token = ms_create_new_token(ms);
				ms_push_token(first_token, second_token);
				first_token = second_token;
				start = start + get_length(string, start);
				first_token->content = ft_substr(string, start, get_length(string, start) + 1);
				if (!string[index + 1])
					break ;
			}
			second_token = ms_create_new_token(ms);
			ms_push_token(first_token, second_token);
			first_token = second_token;
			start++;
		}
		index++;
		if (!string[index])
			first_token->content = ft_substr(string, start, get_length(string, start));
	}
	free(string);
}

/*
 * Parse the pipes which are not already parsed (the ones not separated from space)
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
