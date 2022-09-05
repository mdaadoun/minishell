/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:46:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/05 12:14:15 by mdaadoun         ###   ########.fr       */
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

// cause the shell to exit
void	ms_exit(t_minishell *ms, char **arg)
{
	int nb;
	int i;

	if (ft_count(arg) == 2)
	{
		i = 0;
		nb = 0;
		while (arg[1][i])
		{	
			if (!ft_isdigit(arg[1][i]))
			{
				nb = 2;
				break;
			}
		}
		if (nb)
			ms_set_error(ms->global_error, ERROR_EXIT_ARG, MSG_ERROR_EXIT_ARG);
		else
		{
			ms_set_error(ms->global_error, ERROR_SILENT, NULL);
			nb = ft_atoi(arg[1]);
		}
		ms->exit_status = nb;
	}
	else if (ft_count(arg) > 2)
	{
		ms_set_error(ms->global_error, ERROR_EXTRA_ARGS, MSG_ERROR_EXTRA_ARGS);
		ms->exit_status = 1;
	}
	else
		ms->exit_status = 0;
	exit(ms_free_before_exit(ms));
}
