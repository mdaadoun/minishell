/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:46:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/14 08:24:36 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// run a program in a modified environment
t_uint8	ms_env(t_minishell *ms)
{
	t_variable	*env;

	env = ms->first_var;
	while (env)
	{
		ft_printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
	return (0);
}
