/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 09:03:27 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/06 11:12:39 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	check_char(char c, char d)
{
	if (c == d)
		return (0);
	return (1);
}

static int	check_quote_space(char c)
{
	if (check_char(c, '\'') && check_char(c, '"') && c != ' ')
		return (0);
	return (1);
}

static size_t	init_tok(t_minishell *ms, size_t ind, char *line, char c)
{
	size_t			count;
	bool			no_space;
	t_token_type	type;

	no_space = false;
	count = 0;
	type = NO_TYPE;
	while (check_char(line[ind + count], c) && line[ind + count])
		count++;
	// if (!check_char(line[ind + count], c))
	// {
		if (c == '\'')
			type = TYPE_S_QUOTE_STRING;
		else if (c == '"')
			type = TYPE_D_QUOTE_STRING;
		if (type != NO_TYPE)
		{
			if (line[ind + count + 1] && line[ind + count + 1] != ' ')
				no_space = true;
			ms_add_token(ms, ft_substr(line, ind, count), type, no_space);
		}
		count++;
	// }
	return (count);
}

void	ms_parse_quotes(t_minishell *ms, char *line, size_t ind)
{
	size_t	count;	
	bool	no_space;

	while (line[ind])
	{
		count = 0;
		no_space = false;
		if (line[ind] == ' ')
			count++;
		else if (!check_char(line[ind], '\''))
			count = init_tok(ms, ++ind, line, '\'');
		else if (!check_char(line[ind], '"'))
			count = init_tok(ms, ++ind, line, '"');
		else
		{
			while (line[ind + count] && !check_quote_space(line[ind + count]))
				count++;
			if (line[ind + count] && line[ind + count] != ' ')
				no_space = true;
			ms_add_token(ms, ft_substr(line, ind, count), NO_TYPE, no_space);
		}
		ind += count;
	}
}
