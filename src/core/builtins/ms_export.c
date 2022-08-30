/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:46:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/30 14:46:17 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	print_env_export(t_minishell *ms)
{
	t_variable	*env;

	env = ms->first_var;
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->name, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(env->content, 1);
		ft_putstr_fd("\"\n", 1);
		env = env->next;
	}
}

static size_t	ft_count(char **str)
{
	size_t	ind;

	ind = 0;
	while (str[ind])
		ind++;
	return (ind);
}

/*
 *	set the export attribute for variables
 *  Dynamic structure of variables
 *  check for existing env
 *  replace or create new env
 */
t_uint8	ms_export(t_minishell *ms, char **arg)
{
	size_t		ind;
	t_variable	*env;
	t_variable	*find;

	ind = ft_count(arg);
	if (ind == 1)
		print_env_export(ms);
	else
	{
		ind = 1;
		while (arg[ind])
		{
			env = ft_create_variable(arg[ind]);
			if (env != 0)
			{
				find = ft_get_struct_env(ms, env->name);
				if (find == 0)
					ft_add_variable(ms, env);
				else
					ft_replace_variable(ms, env);
			}
			ind++;
		}
		ms_build_env_tab(ms);
	}
	return (0);
}
