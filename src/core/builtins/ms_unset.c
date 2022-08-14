/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:46:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/14 08:33:49 by dlaidet          ###   ########.fr       */
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

void	ft_remove_env(t_minishell *ms, t_variable *last, t_variable *current)
{
	if (last == 0)
		ms->first_var = current->next;
	else
		last->next = current->next;
	free(current->name);
	free(current->content);
	free(current);
}

static void	check_env(t_minishell *ms, char *arg, t_variable *env)
{
	t_variable	*last;

	last = 0;
	while (env)
	{
		if ((ft_strlen(env->name) - ft_strlen(arg)) != 0)
			env = env->next;
		else if (!ft_strncmp(arg, env->name, ft_strlen(env->name)))
		{
			ft_remove_env(ms, last, env);
			break ;
		}
		last = env;
		env = env->next;
	}	
}

// unset values and attributes of variables and functions
t_uint8	ms_unset(t_minishell *ms, char *cmd)
{
	t_variable	*env;
	char		**arg;
	size_t		ind;

	arg = ft_split(cmd, ' ');
	if (ft_count(arg) == 1)
		return (ft_printf("Printf ERROR: Not enough arguments\n"));
	ind = 1;
	while (arg[ind])
	{
		env = ms->first_var;
		check_env(ms, arg[ind], env);
		ind++;
	}
	return (0);
}
