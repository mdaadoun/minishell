/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:07:09 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/01 15:26:37 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

	// ft_printf("signal:%d", signo);
	if (signo == SIGINT)
		printf("\nYou pressed Ctrl+C\nminishell>");
}

/*
 * Alloc memory and prepare starting data for the minishell.
 * 		path: current working directory
 * 
 * @params:
 *      ms  :   the main minishell data structure to free.
*/
void initialize_minishell(t_minishell **ms)
{
	*ms = (t_minishell *) ft_calloc(sizeof(t_minishell), 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell *ms;
	char	*cmd;
	char	**arg;

	if (argc != 1)
		exit(ms_free_before_exit(NULL, ERROR_PARAMS));
	initialize_minishell(&ms);
	if (DEBUG)
	{
		// run_test(argc, argv, envp);
		exit(ms_free_before_exit(NULL, SUCCESS));
	}
	ms->path = ft_split(getenv("PATH"), ':');
	if (signal(SIGINT, handle_signals) == SIG_ERR)
		printf("Failed\n");
	ms->line = "";
	while (ms->line)
	{
		ms->line = readline("minishell>");
		if (!ms->line)
			exit(ms_free_before_exit(ms, ERROR_UNKNOWN));
		ft_printf("%d\n",rl_catch_signals);
		ft_printf("%s\n", ms->line);
		add_history(ms->line);
		arg = ft_split(ms->line, ' ');
		cmd = ft_get_cmd(ms->path, arg[0]);
		execve(cmd, arg, envp);
		free(ms->line);
	}
	(void)argc;
	(void)argv;
	(void)envp;
	return (ms_free_before_exit(ms, SUCCESS));
}
