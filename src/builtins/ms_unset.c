/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:46:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/06 07:23:52 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	ft_rm_env(t_minishell *ms, t_variable *last, t_variable *current)
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
		if (!ft_strcmp(arg, env->name))
		{
			ft_rm_env(ms, last, env);
			ms_build_env_tab(ms);
			break ;
		}
		last = env;
		env = env->next;
	}	
}

// unset values and attributes of variables and functions
void	ms_unset(t_minishell *ms, char **arg)
{
	t_variable	*env;
	size_t		ind;

	ind = 1;
	while (arg[ind])
	{
		env = ms->first_var;
		check_env(ms, arg[ind], env);
		ind++;
	}
	g_sig.exit_status = 0;
}
