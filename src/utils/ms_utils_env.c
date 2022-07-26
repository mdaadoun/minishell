/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 09:43:39 by dlaidet           #+#    #+#             */
/*   Updated: 2022/09/12 15:33:12 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	ms_envlen(t_variable *env)
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

static void	set_envp(char **envp, t_variable *env)
{
	size_t	ind;
	char	*var;

	ind = 0;
	while (env)
	{
		var = ft_strjoin(env->name, "=");
		if (env->content)
			envp[ind] = ft_strjoin(var, env->content);
		else
			envp[ind] = ft_strdup(var);
		free(var);
		ind++;
		env = env->next;
	}
}

void	ms_build_env_tab(t_minishell *ms)
{
	if (ms->envp)
		ms_free_double_pointer(ms->envp);
	ms->envp = ft_calloc(sizeof(char *), ms_envlen(ms->first_var) + 1);
	ft_protect_malloc(ms, ms->envp);
	set_envp(ms->envp, ms->first_var);
}
