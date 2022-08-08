/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:15:26 by dlaidet           #+#    #+#             */
/*   Updated: 2022/08/04 13:07:13 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	ms_parse_pipe(t_minishell *ms)
{
	t_token	*tok;
	t_token	*tmp;
	size_t	ind;
	char	*str;

	tok = ms->first_token;
	while (tok)
	{
		if (tok->type != 0)
		{
			tok = tok->next;
			continue ;
		}
		ind = 0;
		while (tok->content[ind])
		{
			if (tok->content[ind] == '|')
			{
				if (ind == 0)
					break;
				str = ft_substr(tok->content, 0, ind);
				tmp = ms_create_new_token(ms);
				tmp->content = str;
				ms_append_token(tok->prev, tmp);
				tok->prev = tmp;
				str = ft_substr(tok->content, ind, 1);
				tmp = ms_create_new_token(ms);
				tmp->content = str;
				ms_append_token(tok->prev, tmp);
				tok->prev = tmp;
				tmp->type = TYPE_PIPE;
				ind++;
				str = ft_substr(tok->content, ind, ft_strlen(&tok->content[ind]));
				free(tok->content);
				tok->content = str;
			}
			ind++;
		}
		tok = tok->next;
	}
}
