/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:06:35 by dlaidet           #+#    #+#             */
/*   Updated: 2022/08/17 09:22:17 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static char	*ft_get_env(t_minishell *ms, char *str)
{
	t_variable	*env;

	env = ms->first_var;
	while (env)
	{
		if (ft_strlen(env->name) != ft_strlen(str))
		{
			env = env->next;
			continue ;
		}
		if (!ft_strncmp(env->name, str, ft_strlen(env->name)))
			return (env->content);
		env = env->next;
	}
	return (0);
}

static char	*ft_free_join(char *s1, char *s2, int flag)
{
	char	*new;

	if (!s2)
		s2 = "";
	new = ft_strjoin(s1, s2);
	if (flag == 1 && flag == 0)
		free(s1);
	else if (flag == 2 && flag == 0)
		free(s2);
	return (new);
}

static size_t	ft_strlen_space(char *str)
{
	size_t	ind;

	ind = 0;
	while (str[ind] && str[ind] != ' ')
		ind++;
	return (ind);
}

void	ms_swap_env(t_minishell *ms)
{
	t_token		*tok;
	size_t		ind;
	size_t		lenv;
	char		*s1;
	char		*s2;
	char		*tmp;

	tok = ms->first_token;
	while (tok)
	{
		if (tok->type != TYPE_S_QUOTE_STRING)
		{
			ind = 0;
			while (tok->content[ind])
			{
				if (tok->content[ind++] == '$')
				{
					lenv = 0;
					s1 = ft_substr(tok->content, 0, ind - 1);
					lenv = ft_strlen_space(&tok->content[ind]);
					s2 = ft_substr(tok->content, ind, lenv);
					tmp = ft_get_env(ms, s2);
					tmp = ft_free_join(s1, tmp, 1);
					free(s2);
					ind += lenv;
					lenv = ft_strlen(&tok->content[ind]);
					s2 = ft_substr(tok->content, ind, lenv);
					tmp = ft_free_join(tmp, s2, 0);
					free(tok->content);
					tok->content = tmp;
				}
			}
		}
		tok = tok->next;
	}
}
