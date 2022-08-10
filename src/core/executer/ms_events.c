/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:28:29 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/10 10:14:43 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../inc/minishell.h"


static void	cancel_process(int signo)
{
	// ft_printf("signal:%d", signo);
	if (signo == SIGINT)
	{
		printf("\nYou pressed Ctrl+C\nminishell>");
		// ms_display_prompt(ms);
	}
}

void	ms_initialize_signals(void)
{
	if (signal(SIGINT, cancel_process) == SIG_ERR)
		ft_printf("Failed SIGINT\n");
}
