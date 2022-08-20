/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:46:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/20 07:35:34 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	nb_arg(char **arg)
{
	int	ind;

	ind = 0;
	while (arg[ind])
		ind++;
	return (ind);
}

// display a line of text
t_uint8	ms_echo(char **arg)
{
	int	ind;
	int	n;

	ind = 1;
	n = 0;
	if (nb_arg(arg) > 1)
	{
		while (arg[ind] && ft_strncmp(arg[ind], "-n", 3) == 0)
		{
			n = 1;
			ind++;
		}
		while (arg[ind])
		{
			ft_printf("%s", arg[ind]);
			if (arg[ind + 1] && arg[ind][0] != '\0')
				ft_putchar_fd(' ', 1);
			ind++;
		}
	}
	if (n == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
