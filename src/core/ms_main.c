/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:07:09 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/02 10:33:31 by mdaadoun         ###   ########.fr       */
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
	{
		printf("\nYou pressed Ctrl+C\nminishell>");
		// ms_display_prompt(ms);
	}
}

/*
 * Alloc memory and prepare starting data for the minishell.
 * 		path: current working directory
 * 
 * @params:
 *      ms  :   the main minishell data structure to free.
*/
static void initialize_minishell(t_minishell **ms)
{
	char *buf;

	buf = (char *)ft_calloc(sizeof(char *), 1024);
	if (!buf)
		exit(ms_free_before_exit(*ms, ERROR_ALLOC));
	*ms = (t_minishell *) ft_calloc(sizeof(t_minishell), 1);
	if (!*ms)
		exit(ms_free_before_exit(*ms, ERROR_ALLOC));
	(*ms)->cwd_path = getcwd(buf, 1024);
	(*ms)->line = "";
}

void ms_display_prompt(t_minishell *ms)
{
	printf("%s", ms->cwd_path);
	ms->line = readline(">");
	if (!ms->line)
		exit(ms_free_before_exit(ms, ERROR_UNKNOWN));
	add_history(ms->line);
	ft_printf("%s",ms->line);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell *ms;
	char	*cmd;
	char	**arg;
	char 	**binpath;

	// if (!DEBUG)
	// {
	// 	run_test(argc, argv, envp);
	// 	exit(ms_free_before_exit(NULL, SUCCESS));
	// }
	// if (argc != 1)
	// 	exit(ms_free_before_exit(NULL, ERROR_PARAMS));
	initialize_minishell(&ms);
	binpath = ft_split(getenv("PATH"), ':');
	if (signal(SIGINT, handle_signals) == SIG_ERR)
		printf("Failed\n");
	while (ms->line)
	{
		ms_display_prompt(ms);
		ms_parser(ms); // build data structure from line (space "" '' $ |)
		ms_lexer(ms); // valid command or builtin, valid syntax, checking errors and ignore if not
		ms_executer(ms); // evaluate the command
		arg = ft_split(ms->line, ' ');
		cmd = ft_get_cmd(binpath, arg[0]);
		execve(cmd, arg, envp);
		free(ms->line);
	}
	(void)argc;
	(void)argv;
	(void)envp;
	return (ms_free_before_exit(ms, SUCCESS));
}
