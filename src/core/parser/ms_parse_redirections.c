/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:57:46 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/16 16:57:00 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"


static int get_length(char *string, int start)
{
	int length;

	length = 0;
	if (string[start] == '<' && string[start +1] == '<')
		length++;
	if (string[start] == '>' && string[start +1] == '>')
		length++;
	while (string[start] != '\0' && string[start] != '<' && string[start] != '>')
	{
		length++;
		start++;
	}
	return (length);
}


static void rebuild_redirection_tokens(t_minishell *ms, t_token *token)
{
	t_token	*first_token;
	t_token	*second_token;
	char	*string;
	int		index;
	int 	start;

	start = 0;
	index = 0;
	string = token->content;
	first_token = token;
	while (string[index])
	{
		if (string[index] == '<' || string[index] == '>')
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
					break;
			}
			second_token = ms_create_new_token(ms);
			ms_push_token(first_token, second_token);
			first_token = second_token;
			start++;
		}
		if (	(string[index] == '>' && string[index + 1] == '>') || \
				(string[index] == '<' && string[index + 1] == '<') )
			{
				index += 2;
				start++;
			}
		else
			index++;
		if (!string[index])
			first_token->content = ft_substr(string, start, get_length(string, start));
	}
	free(string);
}

/*
 *	Review all token and find out if there is redirections operators (< << >> >)
 *		Ignore tokens that are already tagged SINGLE or DOUBLE quote
*/
void	ms_parse_redirections(t_minishell *ms)
{
	t_token	*token;
	size_t	i;

	token = ms->first_token;
	while (token)
	{
		if (token->type == TYPE_S_QUOTE_STRING || \
			token->type == TYPE_D_QUOTE_STRING)
		{
			token = token->next;
			continue ;
		}
		i = 0;
		while (token->content[i] && ft_strlen(token->content) > 1)
		{
			if (ft_strlen(token->content) == 2)
				if ( (token->content[i] == '>' && token->content[i + 1] == '>') || \
					 (token->content[i] == '<' && token->content[i + 1] == '<') )
					break;
			if (token->content[i] == '>' || token->content[i] == '<')
				rebuild_redirection_tokens(ms, token);
			i++;
		}
		token = token->next;
	}
}
