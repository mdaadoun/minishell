/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_variable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:21:22 by dlaidet           #+#    #+#             */
/*   Updated: 2022/08/30 14:46:44 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_variable	*ft_create_variable(char	*str)
{
	size_t		ind;
	t_variable	*env;

	ind = 0;
	env = ft_calloc(sizeof(t_variable), 1);
	while (str[ind] && str[ind] != '=')
		ind++;
	if (str[ind] == 0)
		return (0);
	env->name = ft_substr(str, 0, ind);
	if (str[ind] == '=')
	{
		ind++;
		env->content = ft_substr(str, ind, ft_strlen(&str[ind]));
	}
	env->next = 0;
	return (env);
}

void	ft_add_variable(t_minishell *ms, t_variable *env)
{
	t_variable	*var;

	if (!ms->first_var)
		ms->first_var = env;
	else
	{
		var = ms->first_var;
		while (var->next)
			var = var->next;
		var->next = env;
	}
}

void	ft_replace_variable(t_minishell *ms, t_variable *env)
{
	t_variable	*var;

	var = ms->first_var;
	while (var)
	{
		if (!ft_strncmp(var->name, env->name, ft_strlen(env->name) + 1))
		{
			free(var->name);
			var->name = env->name;
			free(var->content);
			var->content = env->content;
			free(env);
			break ;
		}
		var = var->next;
	}
}

void	ms_copy_env(t_minishell *ms, char **envp)
{
	int	ind;

	ind = 0;
	while (envp[ind])
	{
		ft_add_variable(ms, ft_create_variable(envp[ind]));
		ind++;
	}
}

char	*ft_get_env(t_minishell *ms, char *str)
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
