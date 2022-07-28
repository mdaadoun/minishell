/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:07:09 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/07/28 14:53:54 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	handle_signals(int signo)
{
	if (signo == SIGINT)
		printf("\nYou pressed Ctrl+C\n|-->");
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**path;
	char	*cmd;
	char	**arg;

	path = ft_split(getenv("PATH"), ':');
	if (signal(SIGINT, handle_signals) == SIG_ERR)
		printf("Failed\n");
	while (1)
	{
		input = readline("|-->");
		if (!input)
			break;
		ft_printf("%s\n", input);
		add_history(input);
		arg = ft_split(input, ' ');
		cmd = ft_get_cmd(path, arg[0]);
		execve(cmd, arg, envp);
		free(input);
	}
	(void)ac;
	(void)av;
	return (0);
}
