/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:46:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/08 14:48:42 by dlaidet          ###   ########.fr       */
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

static t_variable	*ft_create_env(char	*str)
{
	size_t	ind;
	t_variable	*env;

	ind = 0;
	env = malloc(sizeof(t_variable) * 1);
	while (str[ind] && str[ind] != '=')
		ind++;
	if (str[ind])
		return (0);
	if (str[ind] != '=')
	{
		env->name = ft_substr(str, 0, ind);
		ind += 2;
		env->content = ft_substr(str, ind, ft_strlen(&str[ind]));
	}
	env->next = 0;
}

static void	ft_add_env(t_minishell *ms, t_variable *env)
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

/*
 * Dynamic structure of variables
*/
t_uint8 ms_export(t_minishell *ms, char *cmd)
{
	char	**arg;
	size_t	ind;

	arg = ft_split(cmd, ' ');
	ind = ft_count(arg);
	if (ind == 1)
		ms_env(ms);
	else
	{
		ind = 1;
		while (arg[ind])
		{
			ft_add_env(ms, ft_create_env(arg[ind]));
			ind++;
		}
	}
    return (SUCCESS);
}
