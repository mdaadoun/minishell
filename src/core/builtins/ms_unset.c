/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:46:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/10 09:08:04 by dlaidet          ###   ########.fr       */
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

// unset values and attributes of variables and functions
t_uint8 ms_unset(t_minishell *ms, char *cmd)
{
	t_variable *env;
	t_variable	*last;	
	char	**arg;
	size_t	ind;
	int	dif;

	arg = ft_split(cmd, ' ');
	ind = ft_count(arg);
	if (ind == 1)
		return (ft_printf("Printf ERROR: Not enough arguments\n"));
	ind = 1;
	while (arg[ind])
	{
		last = 0;
		env = ms->first_var;
		while (env)
		{
			dif = ft_strlen(env->name) - ft_strlen(arg[ind]);
			if (dif != 0)
				{
				env = env->next;
				continue;
			}
			if (!ft_strncmp(arg[ind], env->name, ft_strlen(env->name)))
			{
				ft_remove_env(ms, last, env);
				break;
			}
			last = env;
			env = env->next;
		}	
		ind++;
	}
	return (0);
}
