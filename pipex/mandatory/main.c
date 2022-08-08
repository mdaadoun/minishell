/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 08:06:53 by dlaidet           #+#    #+#             */
/*   Updated: 2022/06/09 08:06:54 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	ft_close_pipe(t_var *var)
{
	close(var->pipe[0]);
	close(var->pipe[1]);
	return ;
}

void	ft_close_file(t_var *var)
{
	close(var->infile);
	close(var->outfile);
	return ;
}

void	ft_free_path(t_var *var)
{
	int	ind;

	ind = 0;
	while (var->cmd_path[ind])
	{
		free(var->cmd_path[ind]);
		ind++;
	}
	free(var->cmd_path);
	return ;
}

int	main(int ac, char **av, char **envp)
{
	t_var	var;

	ft_check_arg(ac, av, &var);
	var.cmd_path = ft_split(ft_find_path(envp), ':');
	var.pid1 = fork();
	if (var.pid1 == 0)
		ft_first_child(&var, av, envp);
	var.pid2 = fork();
	if (var.pid2 == 0)
		ft_second_child(&var, av, envp);
	ft_close_pipe(&var);
	waitpid(var.pid1, NULL, 0);
	waitpid(var.pid2, NULL, 0);
	ft_close_file(&var);
	ft_free_path(&var);
	return (0);
}
