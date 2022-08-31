/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sorting_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 07:16:24 by dlaidet           #+#    #+#             */
/*   Updated: 2022/08/31 10:37:59 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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
	size_t	it;
	size_t	let;

	envp = ms->envp;
	len = envplen(envp);
	ind = 0;
	let = 0;
	while (ind < len)
	{
		it = ind + 1;
		while (envp[ind][let] < envp[it][let] && it < len)
			it++;
		while (envp[ind][let] == envp[it][let] && envp[ind][let] && envp[it][let])
			let++;
		if (envp[ind][let] > envp[it][let])
		{
			swap_envp(&envp[ind], &envp[it]);
			ind = 0;
			let = 0;
		}
		else
			ind++;
	}
}
