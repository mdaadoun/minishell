/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:46:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/22 06:36:25 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static size_t	ft_count(char **str)
{
	size_t	ind;

	ind = 0;
	while (str[ind])
		ind++;
	return (ind);
}

static t_variable	*ft_create_variable(char	*str)
{
	size_t		ind;
	t_variable	*env;

	ind = 0;
	env = malloc(sizeof(t_variable) * 1);
	while (str[ind] && str[ind] != '=')
		ind++;
	if (!str[ind])
		return (0);
	if (str[ind] == '=')
	{
		env->name = ft_substr(str, 0, ind);
		ind++;
		env->content = ft_substr(str, ind, ft_strlen(&str[ind]));
	}
	env->next = 0;
	return (env);
}

static void	ft_add_variable(t_minishell *ms, t_variable *env)
{
	t_variable	*var;

	if (!ms->first_var)
		ms->first_var = env;
	else
	{
		var = ms->first_var;
		while (var->next)
		{
//			ft_printf("%s=%s\n", var->name, var->content);
			var = var->next;
		}
		var->next = env;
	}
}

/*
 *	set the export attribute for variables
 *  Dynamic structure of variables
 *  check for existing env
 *  replace or create new env
 */
t_uint8	ms_export(t_minishell *ms, char **arg)
{
	size_t	ind;

	ind = ft_count(arg);
	if (ind == 1)
		ms_env(ms);
	else
	{
		ind = 1;
		while (arg[ind])
		{
			ft_add_variable(ms, ft_create_variable(arg[ind]));
			ind++;
		}
	}
	return (0);
}

void	ms_copy_env(t_minishell *ms)
{
	int	ind;

	ind = 0;
	while (ms->envp[ind])
	{
		ft_add_variable(ms, ft_create_variable(ms->envp[ind]));
		ind++;
	}
}
