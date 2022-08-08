/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:07:09 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/08 10:58:11 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Alloc memory and prepare starting data for the minishell.
 * 		path: current working directory
 * 
 * @params:
 *      ms  :   the main minishell data structure to free.
*/
void	ms_initialize_minishell(t_minishell **ms)
{
	char *buf;

	if (!DEBUG)
		ft_printf("%s", MINISHELL_LOGO);
	buf = (char *)ft_calloc(sizeof(char), 1024);
	if (!buf)
		exit(ms_free_before_exit(*ms, ERROR_ALLOC));
	*ms = (t_minishell *) ft_calloc(sizeof(t_minishell), 1);
	if (!*ms)
		exit(ms_free_before_exit(*ms, ERROR_ALLOC));
	(*ms)->cwd_path = getcwd(buf, 1024);
	(*ms)->bin_paths = ft_split(getenv("PATH"), ':');
	(*ms)->full_line = "";
}

/*
 * Display working directory prompt and get line with readline.
 *	Add the line to the history.
*/
static void display_prompt_and_wait(t_minishell *ms)
{
	printf("\e[1;38m%s\e[m", ms->cwd_path);
	ms->full_line = readline(">");
	if (!ms->full_line)
		exit(ms_free_before_exit(ms, ERROR_UNKNOWN));
	add_history(ms->full_line);
}

/*
 *	>> MINISHELL <<
 *		REPL : READ > EVALUATE > PRINT > LOOP
 *			1) Parser: Data structure of tokens (tokenization).
 *			2) Lexer: Lexical analysis of tokens (evaluation).
 *			3) Executer: Fork processes, run and print result.
 *			4) Loop: Free data and wait for the next command.
*/
int	main(int argc, char **argv, char **envp)
{
	t_minishell *ms;

	if (DEBUG)
		run_test(argc, argv, envp);
	if (argc != 1)
		exit(ms_free_before_exit(NULL, ERROR_PARAMS));
	ms_initialize_minishell(&ms);
	ms->envp = envp;
	if (signal(SIGINT, ft_SIGINT) == SIG_ERR)
		ft_printf("Failed SIGINT\n");
	if (signal(SIGQUIT, ft_SIGQUIT) == SIG_ERR)
	{
		ft_printf("Failed SIGQUIT\n");
	}
	while (ms->full_line)
	{
		display_prompt_and_wait(ms);
		if (ft_strlen(ms->full_line))
		{
			ms_parser(ms);
			ms_lexer(ms);
			ms_executer(ms);
		}
		ms_free_last_command(ms);
	}
	return (ms_free_before_exit(ms, SUCCESS));
}
