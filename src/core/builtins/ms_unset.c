/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:46:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/23 16:07:56 by mdaadoun         ###   ########.fr       */
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

static void	ft_remove_env(t_minishell *ms, t_variable *last, t_variable *current)
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
t_uint8	ms_unset(t_minishell *ms, char **arg)
{
	t_variable	*env;
	size_t		ind;
	t_err_key	err_key;
	char		*err_msg;

	err_key = ERROR_MISSING_ARGS;
	err_msg = MSG_ERROR_MISSING_ARGS;
	if (ft_count(arg) == 1)
	{
		ms_set_error(ms->global_error, err_key, err_msg);
		return (1);
	}
	ind = 1;
	while (arg[ind])
	{
		env = ms->first_var;
		check_env(ms, arg[ind], env);
		ind++;
	}
	return (0);
}
