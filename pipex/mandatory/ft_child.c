/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 07:36:41 by dlaidet           #+#    #+#             */
/*   Updated: 2022/06/23 07:36:43 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*ft_get_cmd(char **path, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		path++;
	}
	return (NULL);
}

void	ft_free_child(t_var *var)
{
	int	ind;

	ind = 0;
	while (var->arg[ind])
	{
		free(var->arg[ind]);
		ind++;
	}
	free(var->arg);
	ft_free_path(var);
}

void	ft_first_child(t_var *var, char **av, char **envp)
{
	dup2(var->pipe[1], 1);
	close(var->pipe[0]);
	dup2(var->infile, 0);
	var->arg = ft_split(av[2], ' ');
	var->cmd = ft_get_cmd(var->cmd_path, var->arg[0]);
	if (!var->cmd)
	{
		ft_free_child(var);
		ft_error("Invalid command\n");
		exit(1);
	}
	execve(var->cmd, var->arg, envp);
}

void	ft_second_child(t_var *var, char **av, char **envp)
{
	dup2(var->pipe[0], 0);
	close(var->pipe[1]);
	dup2(var->outfile, 1);
	var->arg = ft_split(av[3], ' ');
	var->cmd = ft_get_cmd(var->cmd_path, var->arg[0]);
	if (!var->cmd)
	{
		ft_free_child(var);
		ft_error("Invalid command\n");
		exit(1);
	}
	execve(var->cmd, var->arg, envp);
}
