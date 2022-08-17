/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 09:03:27 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/17 08:50:08 by dlaidet          ###   ########.fr       */
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
	if (check_char(c, 39) && check_char(c, 34) && c != ' ')
		return (0);
	return (1);
}

static size_t	init_tok(t_minishell *ms, size_t ind, char *line, char c)
{
	char	*content;
	size_t	count;

	count = 0;
	while (check_char(line[ind + count], c) && line[ind + count])
		count++;
	if (!check_char(line[ind + count], c))
	{
		content = ft_substr(line, ind, count);
		if (c == 39)
			ms_add_token(ms, content, TYPE_S_QUOTE_STRING);
		else if (c == 34)
			ms_add_token(ms, content, TYPE_D_QUOTE_STRING);
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

	line = ms->full_command;
	ind = 0;
	while (line[ind])
	{
		count = 0;
		if (line[ind] == ' ')
			count++;
		else if (!check_char(line[ind], 39))
			count = init_tok(ms, ++ind, line, 39);
		else if (!check_char(line[ind], 34))
			count = init_tok(ms, ++ind, line, 34);
		else
		{
			while (line[ind + count] && !check_quote_space(line[ind + count]))
				count++;
			content = ft_substr(line, ind, count);
			ms_add_token(ms, content, NO_TYPE);
		}
		ind += count;
	}
}
