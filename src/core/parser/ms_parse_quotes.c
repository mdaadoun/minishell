/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 09:03:27 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/29 11:13:25 by mdaadoun         ###   ########.fr       */
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
	char	*content;
	size_t	count;
	bool	no_space;

	no_space = false;
	count = 0;
	while (check_char(line[ind + count], c) && line[ind + count])
		count++;
	if (!check_char(line[ind + count], c))
	{
		content = ft_substr(line, ind, count);
		if (c == '\'')
		{
			if (line[ind + count + 1] && line[ind + count + 1] != ' ')
				no_space = true;
			ms_add_token(ms, content, TYPE_S_QUOTE_STRING, no_space);
		}
		else if (c == '"')
		{
			if (line[ind + count + 1] && line[ind + count + 1] != ' ')
				no_space = true;
			ms_add_token(ms, content, TYPE_D_QUOTE_STRING, no_space);
		}
		count++;
	}
	return (count);
}

void	ms_parse_quotes(t_minishell *ms)
{
	size_t	ind;
	size_t	count;	
	char	*line;
	char	*content;
	bool	no_space;

	line = ms->full_command;
	ind = 0;
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
			content = ft_substr(line, ind, count);
			ms_add_token(ms, content, NO_TYPE, no_space);
		}
		ind += count;
	}
}
