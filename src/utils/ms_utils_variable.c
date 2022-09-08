/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_variable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:21:22 by dlaidet           #+#    #+#             */
/*   Updated: 2022/09/05 13:04:59 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_variable	*ft_create_variable(t_minishell *ms, char	*str)
{
	size_t		ind;
	t_variable	*env;
	char		*tmp;

	ind = ft_strlen_arg(str, '=');
	if (str[ind] == 0)
		return (0);
	env = ft_calloc(sizeof(t_variable), 1);
	if (str[ind - 1] == '+' && str[ind] == '=')
	{
		env->name = ft_substr(str, 0, ind - 1);
		tmp = ft_substr(str, ind + 1, ft_strlen(&str[ind + 1]));
		env->content = ft_get_env(ms, env->name);
		if (!env->content)
			env->content = "";
		env->content = ft_strjoin(env->content, tmp);
		free(tmp);
	}
	else if (str[ind] == '=')
	{
		env->name = ft_substr(str, 0, ind);
		ind++;
		env->content = ft_substr(str, ind, ft_strlen(&str[ind]));
	}
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
		ft_add_variable(ms, ft_create_variable(ms, envp[ind]));
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
