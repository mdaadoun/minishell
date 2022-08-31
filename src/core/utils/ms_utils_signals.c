/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:28:29 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/31 15:00:37 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
 *		1. If Ctrl+C, display back the prompt (need the current working dir).
 *		2. If Ctrl+\, ugly hack to hide ^\. Do nothing.
*/
static void	cancel_process(int signo)
{
	if (signo == SIGINT)
	{
		if (g_sig.in_heredoc)
		{
			write(1, "^C", 2);
			g_sig.in_heredoc = false;	
			exit(0);
		}
		else
		{
			if (!g_sig.in_child)
				write(1, "^C\n", 3);
			if (g_sig.in_process)
				g_sig.in_process = false;
			else
			{
				rl_on_new_line();
				rl_replace_line("", 0);
				rl_redisplay();
			}
		}

	}
	if (signo == SIGQUIT)
	{
		if (!g_sig.in_child)
			return ;
	}
}

/*
 *	Ctrl+C == SIGINT && Ctrl+\ == SIGQUIT
 *	tcgetattr and tcsetattr used to remove default ^X
*/
void	ms_initialize_signals(void)
{
	struct termios	terminal;
	
	tcgetattr(STDIN_FILENO, &terminal);
	terminal.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	if (signal(SIGINT, cancel_process) == SIG_ERR)
		write(2, "\e[0;31mError: Failed SIGINT signal.\e[m\n", 39);
	if (signal(SIGQUIT, cancel_process) == SIG_ERR)
		write(2, "\e[0;31mError: Failed SIGQUIT signal.\e[m\n", 40);
}
