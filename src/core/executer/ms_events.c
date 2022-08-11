/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:28:29 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/11 15:51:18 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../inc/minishell.h"


static void	cancel_process(int signo)
{
	if (signo == SIGINT)
		printf("\nYou pressed Ctrl+C\n");
}

void	ms_initialize_signals(void)
{
	if (signal(SIGINT, cancel_process) == SIG_ERR)
		ft_printf("Failed SIGINT\n");
}
