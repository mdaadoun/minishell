/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:46:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/12 09:29:56 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// run a program in a modified environment
t_uint8 ms_env(t_minishell *ms)
{
	int ind;
	t_variable *env;

	ind = 0;
	env = 0;
	while(ms->envp[ind])
		ft_printf("%s\n", ms->envp[ind++]);
	ft_printf("Env: %p\n", ms->first_var);
	env = ms->first_var;
	ft_printf("Env: %p\n", env);
	while (env)
	{
		ft_printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
	return (0);
}
