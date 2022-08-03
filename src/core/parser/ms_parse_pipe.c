/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:15:26 by dlaidet           #+#    #+#             */
/*   Updated: 2022/08/03 14:49:49 by dlaidet          ###   ########.fr       */
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
		ind = 0;
		while (tok->content[ind])
		{
			if (tok->content[ind] == '|')
			{
				str = ft_substr(tok->content, 0, ind);
				tmp = ms_create_new_token(ms);
				ms_replace_token(tok, tmp);
				tmp->content = str;
				str = ft_substr(tok->content, ind, 1);
				tmp = ms_create_new_token(ms);
				tmp->content = str;
				ms_append_token(tok->next->prev, tmp);
				str = ft_substr(tok->content, ind + 1, ft_strlen(&tok->content[ind + 1]));
				free(tok->content);
				tok->content = str;
			}
			ind++;
		}
		if (tok->next->prev != tok)
			tok = tmp;
		else
			tok = tok->next;
	}
}

void	ms_replace_token(t_token *old, t_token *new)
{
	old->next->prev = new;
	old->prev->next = new;
	new->next = old->next;
	new->prev = old->prev;
}
