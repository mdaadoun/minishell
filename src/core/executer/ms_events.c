/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:28:29 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/23 14:55:05 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
 *		1. If Ctrl+C, display back the prompt (need the current working dir).
 *		2. If Ctrl+\, ugly hack to hide ^\. Do nothing.
*/
static void	cancel_process(int signo)
{
	char	*buf;
	char 	*cwd_path;

	buf = (char *)ft_calloc(sizeof(char), 1024);
	cwd_path = getcwd(buf, 1024);
	if (signo == SIGINT)
		printf("\n\e[0;34m%s\e[m\e[0;36m>\e[m", cwd_path);
	if (signo == SIGQUIT)
	{
		ft_printf("\b\b  \b\b");
		return ;
	}
	free(cwd_path);
}

// Ctrl+C == SIGINT && Ctrl+\ == SIGQUIT
void	ms_initialize_signals(void)
{
	if (signal(SIGINT, cancel_process) == SIG_ERR)
		write(2, "\e[0;31mError: Failed SIGINT signal.\e[m\n", 39);
	if (signal(SIGQUIT, cancel_process) == SIG_ERR)
		write(2, "\e[0;31mError: Failed SIGQUIT signal.\e[m\n", 40);
}
