/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sorting_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 07:16:24 by dlaidet           #+#    #+#             */
/*   Updated: 2022/09/05 07:01:35 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	int	a;
	int	compt;

	compt = 0;
	a = 0;
	while (a == 0 && (s1[compt] != '\0' || s2[compt] != '\0'))
	{
		a = s1[compt] - s2[compt];
		compt++;
	}
	return (a);
}

static size_t	envplen(char **envp)
{
	size_t	len;

	len = 0;
	while (envp[len])
		len++;
	return (len);
}

static void	swap_envp(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	s1 = s2;
	s2 = &tmp;
}

void	ms_sorting_env(t_minishell *ms)
{
	char	**envp;
	size_t	len;
	size_t	ind;

	envp = ms->envp;
	len = envplen(envp);
	ind = 0;
	while (ind < len)
	{
	}
}
