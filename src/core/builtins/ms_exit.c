/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:46:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/08 09:28:13 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	run_exit(t_minishell *ms, char **arg)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (arg[1][i])
	{	
		if (!ft_isdigit(arg[1][i]))
		{
			nb = 2;
			break ;
		}
		i++;
	}
	if (nb == 2)
		ms_set_error(ms->global_error, ERROR_EXIT_ARG, MSG_ERROR_EXIT_ARG);
	else
	{
		ms_set_error(ms->global_error, ERROR_SILENT, NULL);
		nb = ft_atoi(arg[1]) % 256;
	}
	g_sig.exit_status = nb;
}

// cause the shell to exit
void	ms_exit(t_minishell *ms, char **arg)
{
	int			nb;
	t_err_key	err_key;
	char		*err_msg;

	err_key = ERROR_EXTRA_ARGS;
	err_msg = MSG_ERROR_EXTRA_ARGS;
	nb = ft_count_tab_string(arg);
	if (nb >= 2)
	{
		run_exit(ms, arg);
		if (g_sig.exit_status != 2 && nb > 2)
		{
			ms_set_error(ms->global_error, err_key, err_msg);
			g_sig.exit_status = 1;
		}
		else
			exit(ms_free_before_exit(ms));
	}
	else
		exit(ms_free_before_exit(ms));
}
