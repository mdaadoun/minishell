/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:06:35 by dlaidet           #+#    #+#             */
/*   Updated: 2022/08/03 11:40:55 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	ms_swap_env(t_minishell *ms)
{
	t_token	*tok;
	size_t	ind;
	size_t	lenv;
	char	*s1;
	char	*s2;
	char	*new;

	tok = ms->first_token;
	while (tok)
	{
		ind = 0;
		while (tok->content[ind])
		{
			if (tok->content[ind] == '$')
			{
				lenv = 0;
				s1 = ft_substr(tok->content, 0, ind);
				while (tok->content[ind + lenv] && tok->content[ind +lenv] != ' ')
					lenv++;
				s2 = ft_substr(tok->content, ind + 1, lenv);
				new = ft_strjoin(s1, getenv(s2));
				free(s1);
				free(s2);
				ind += lenv;
				lenv = 0;
				while (tok->content[ind + lenv])
					lenv++;
				s2 = ft_substr(tok->content, ind, lenv);
				s1 = new;
				new = ft_strjoin(s1, s2);
				free(s1);
				free(s2);
				free(tok->content);
				tok->content = new;
			}
			ind++;
		}
		tok = tok->next;
	}
}
