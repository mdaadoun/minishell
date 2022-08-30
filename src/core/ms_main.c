/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:07:09 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/30 10:03:24 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 *	Initialization of the minishell main data structure.
 */
void	ms_initialize_minishell(t_minishell **ms, t_error *error, char **envp)
{
	char	*buf;

	if (!DEBUG)
		ft_printf("%s", MINISHELL_LOGO);
	*ms = (t_minishell *) ft_calloc(sizeof(t_minishell), 1);
	if (!*ms)
	{
		write(2, MSG_ERROR_MALLOC, 41);
		exit(EXIT_FAILURE);
	}
	error->flag = false;
	(*ms)->global_error = error;
	buf = (char *)ft_calloc(sizeof(char), 1024);
	if (!buf)
	{
		ms_set_error((*ms)->global_error, ERROR_MALLOC, MSG_ERROR_MALLOC);
		exit(ms_free_before_exit(*ms));
	}
	(*ms)->cwd_path = getcwd(buf, 1024);
	(*ms)->bin_paths = ft_split(getenv("PATH"), ':');
	(*ms)->full_command = "";
	ms_copy_env(*ms, envp);
	ms_build_env_tab((*ms));
}

/*
 *	Steps for the prompt and catching input:
 *		1. Display working directory prompt.
 *		2. Get line from input with readline.
 *		3. The Ctrl-D is controlled with "if (!ms->full_command)"
 *		4. Add the line to the history.
 */
static void	display_prompt_and_wait(t_minishell *ms)
{
	char	*prompt;
	char	*swp;

	prompt = ft_strjoin("\e[0;34m", ms->cwd_path);
	swp = prompt;
	prompt = ft_strjoin(prompt, "\e[m\e[0;36m>\e[m");
	free(swp);
	ms->full_command = readline(prompt);
	free(prompt);
	if (!ms->full_command)
	{
		ft_printf("exit\n");
		exit(ms_free_before_exit(ms));
	}
	if (ft_strlen(ms->full_command) > 0)
		add_history(ms->full_command);
}

/*
 *
 *	>> MINISHELL <<
 *		1. Initialize the minishell main data structure.
 *		2. Initialize signals.
 *		3. Infinite loop:
 *			1) Display the prompt and wait for input.
 *			2) Parser: Data structure of tokens (tokenization).
 *			3) Analyzer: Lexical analysis of tokens (evaluation).
 *			4) Executer: Build processes, run pipeline and print result if any.
 *			5) Free data from the last command.
 *			6) Print error if any and reset error data for the next loop.
 *
 */
int	main(int argc, char **argv, char **envp)
{
	t_minishell	*ms;
	t_error		error;

	if (DEBUG)
		test_start(argc, argv, envp);
	ms_initialize_minishell(&ms, &error, envp);
	ms_initialize_signals();
	while (true)
	{
		display_prompt_and_wait(ms);
		if (ft_strlen(ms->full_command))
		{
			ms_parser(ms);
			ms_analyzer(ms);
			ms_executer(ms);
		}
		ms_free_last_command(ms);
		if (ms->global_error->flag)
			ms_print_error(ms);
		ms_set_error(ms->global_error, NO_ERROR, NULL);
	}
	return (ms_free_before_exit(ms));
}
