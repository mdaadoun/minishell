/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:28:29 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/18 13:43:39 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	cancel_process(int signo)
{
	if (signo == SIGINT)
		printf("\nYou pressed Ctrl+C\n");
	if (signo == SIGQUIT)
		printf("\nYou pressed Ctrl+\\\n");
		// return ;
}

void	ms_initialize_signals(void)
{
	if (signal(SIGINT, cancel_process) == SIG_ERR)
		ft_printf("Failed SIGINT\n");
	if (signal(SIGQUIT, cancel_process) == SIG_ERR)
		ft_printf("Failed SIGQUIT\n");
}
