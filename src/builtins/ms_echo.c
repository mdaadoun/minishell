/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:46:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/12 17:30:16 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	nb_arg(char **arg)
{
	int	ind;

	ind = 0;
	while (arg[ind])
		ind++;
	return (ind);
}

static void	print_echo(char **arg, int ind)
{
	while (arg[ind])
	{
		ft_printf("%s", arg[ind]);
		if (arg[ind + 1] && arg[ind][0] != '\0')
			ft_putchar_fd(' ', 1);
		ind++;
	}
}

static bool	check_arg(char **arg, int ind)
{
	int	i;

	i = 1;
	if (arg[ind][i] == '\0')
		return (true);
	while (arg[ind][i] == 'n')
		i++;
	if (arg[ind][i] && arg[ind][i] != 'n')
		return (true);
	return (false);
}

// display a line of text
void	ms_echo(char **arg)
{
	int		ind;
	bool	n;
	bool	c;

	ind = 1;
	n = true;
	if (nb_arg(arg) > 1)
	{
		while (arg[ind] && arg[ind][0] == '-')
		{
			c = check_arg(arg, ind);
			if (c == false)
				n = false;
			if (c == true)
				break ;
			ind++;
		}
		print_echo(arg, ind);
	}
	if (n == true)
		ft_putchar_fd('\n', 1);
	g_sig.exit_status = 0;
}
