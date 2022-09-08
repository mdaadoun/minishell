/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:46:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/06 07:52:16 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// run a program in a modified environment
void	ms_env(t_minishell *ms)
{
	t_variable	*env;

	env = ms->first_var;
	while (env)
	{
		ft_putstr_fd(env->name, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(env->content, 1);
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
	g_sig.exit_status = 0;
}
