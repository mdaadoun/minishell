/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:06:35 by dlaidet           #+#    #+#             */
/*   Updated: 2022/09/07 09:21:44 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static char	*ft_free_join(char *s1, char *s2, int flag)
{
	char	*new;

	if (!s2)
		s2 = "";
	new = ft_strjoin(s1, s2);
	if (flag == 1 || flag == 0)
		free(s1);
	if (flag == 2 || flag == 0)
		free(s2);
	return (new);
}

static size_t	ft_strlen_space(char *str)
{
	size_t	ind;

	ind = 0;
	while (str[ind] && str[ind] != ' ' && str[ind] != '$' \
	&& str[ind] != '\'' && str[ind] != '\"')
		ind++;
	return (ind);
}

static char	*swap_exit_status(char	*s1)
{
	char		*ret;

	ret = ft_free_join(s1, ft_itoa(g_sig.exit_status), 0);
	if (g_sig.exit_status == 130)
		g_sig.exit_status = 0;
	return (ret);
}

static void	swap(t_minishell *ms, t_token *tok, size_t ind)
{
	size_t		lenv;
	char		*s1;
	char		*s2;
	char		*tmp;

	lenv = 0;
	s1 = ft_substr(tok->content, 0, ind);
	lenv = ft_strlen_space(&tok->content[ind + 1]);
	if (lenv == 1 && tok->content[ind + 1] == '?')
		tmp = swap_exit_status(s1);
	else
	{
		s2 = ft_substr(tok->content, ind + 1, lenv);
		tmp = ft_free_join(s1, ft_get_env(ms, s2), 1);
		free(s2);
	}
	ind += lenv + 1;
	lenv = ft_strlen(&tok->content[ind]);
	s2 = ft_substr(tok->content, ind, lenv);
	tmp = ft_free_join(tmp, s2, 0);
	free(tok->content);
	tok->content = tmp;
}

void	ms_swap_env(t_minishell *ms)
{
	t_token		*tok;
	size_t		ind;

	tok = ms->first_token;
	while (tok)
	{
		if (tok->type != TYPE_S_QUOTE_STRING)
		{
			ind = 0;
			while (tok->content[ind])
			{
				if (tok->content[ind] == '$')
					swap(ms, tok, ind);
				else
					ind++;
			}
		}
		tok = tok->next;
	}
}
