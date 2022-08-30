/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:28:29 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/30 17:48:51 by mdaadoun         ###   ########.fr       */
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
		write(1, "\n", 1);
		if (g_sig->in_heredoc)
		{
			g_sig->in_heredoc = false;
			exit(0);
		}
		else
		{
			if (g_sig->in_process)
				g_sig->in_process = false;
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
		ft_printf("\b\b  \b\b");
		return ;
	}
}

// Ctrl+C == SIGINT && Ctrl+\ == SIGQUIT
void	ms_initialize_signals(void)
{
	if (signal(SIGINT, cancel_process) == SIG_ERR)
		write(2, "\e[0;31mError: Failed SIGINT signal.\e[m\n", 39);
	if (signal(SIGQUIT, cancel_process) == SIG_ERR)
		write(2, "\e[0;31mError: Failed SIGQUIT signal.\e[m\n", 40);
}
