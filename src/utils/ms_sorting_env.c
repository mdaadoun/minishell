/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sorting_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 07:16:24 by dlaidet           #+#    #+#             */
/*   Updated: 2022/09/05 09:11:24 by mdaadoun         ###   ########.fr       */
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

void	ms_sorting_env(t_minishell *ms)
{
	char	**envp;
	size_t	len;
	size_t	ind;
	size_t	var;
	char	*tmp;

	envp = ms->envp;
	len = envplen(envp);
	ind = 0;
	while (ind < len)
	{
		var = ind + 1;
		while (var < len)
		{
			if (ft_strcmp(envp[ind], envp[var]) > 0)
			{
				tmp = envp[ind];
				envp[ind] = envp[var];
				envp[var] = tmp;
			}
			var++;
		}
		ind++;
	}
}
