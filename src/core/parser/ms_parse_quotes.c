/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 09:03:27 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/10 07:45:13 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	ms_parse_quotes(t_minishell *ms)
{
	size_t	ind;
	size_t	count;	
	char	*line;
	char	*content;

	line = ms->full_command;
	ind = 0;
	count = 0;
	while (line[ind])
	{
		if (line[ind] == ' ')
		{
			count++;
		}
		else if (line[ind] == 39)
		{
			ind++;
			while (line[ind + count] != 39 && line[ind + count])
			{
				count++;
			}
			if (line[ind + count] == 39)
			{
				content = ft_substr(line, ind, count);
				ms_add_token(ms, content, TYPE_S_QUOTE_STRING);
				count++;
			}
		}
		else if (line[ind] == 34)
		{
			ind++;
			while (line[ind + count] != 34 && line[ind + count])
			{
				count++;
			}
			if (line[ind + count] == 34)
			{
				content = ft_substr(line, ind, count);
				ms_add_token(ms , content, TYPE_D_QUOTE_STRING);
				count++;
			}
		}
		else
		{
			while (line[ind + count] && line[ind + count] != ' ' && line[ind + count] != 39 && line[ind + count] != 34)
			{
				count++;
			}
			content = ft_substr(line, ind, count);
			ms_add_token(ms, content, NO_TYPE);
		}
		ind += count;
		count = 0;
	}
}
