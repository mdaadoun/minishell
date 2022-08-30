/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 09:43:39 by dlaidet           #+#    #+#             */
/*   Updated: 2022/08/30 10:20:10 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static size_t	envlen(t_variable *env)
{
	size_t	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

void	ms_free_envp(char **envp)
{
	size_t	ind;

	ind = 0;
	while (envp[ind])
	{
		free(envp[ind]);
		ind++;
	}
	free(envp);
}

static void	set_envp(char **envp, t_variable *env)
{
	size_t	ind;
	char	*var;

	ind = 0;
	while (env)
	{
		var = ft_strjoin(env->name, "=");
		envp[ind] = ft_strjoin(var, env->content);
		free(var);
		ind++;
		env = env->next;
	}
}

void	ms_build_env_tab(t_minishell *ms)
{
	if (ms->envp)
		ms_free_envp(ms->envp);
	ms->envp = ft_calloc(sizeof(char *), envlen(ms->first_var) + 1);
	set_envp(ms->envp, ms->first_var);
}
