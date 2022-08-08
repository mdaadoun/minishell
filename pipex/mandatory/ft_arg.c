/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 08:30:32 by dlaidet           #+#    #+#             */
/*   Updated: 2022/06/09 08:30:34 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_arg_file(int ac, char **av, t_var *var)
{
	var->infile = open(av[1], O_RDONLY);
	if (var->infile < 0)
		ft_perror("Invalid InFile\n");
	var->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (var->outfile < 0)
		ft_perror("Invalid OutFile\n");
	return ;
}

void	ft_check_arg(int ac, char **av, t_var *var)
{
	if (ac != 5)
		ft_error("Not enough argument\n");
	ft_arg_file(ac, av, var);
	if (pipe(var->pipe) < 0)
		ft_perror("Pipe Error\n");
}
