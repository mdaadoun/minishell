/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:46:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/22 10:25:06 by dlaidet          ###   ########.fr       */
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
	char		*str;

	ind = ft_count(arg);
	if (ind == 1)
		ms_env(ms);
	else
	{
		ind = 1;
		while (arg[ind])
		{
			env = ft_create_variable(arg[ind]);
			str = ft_get_env(ms, env->name);
			if (str == 0)
				ft_add_variable(ms, env);
			else
				ft_replace_variable(ms, env);
			ind++;
		}
	}
	return (0);
}
