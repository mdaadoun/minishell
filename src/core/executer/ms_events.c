/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:00:10 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/06 09:31:22 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	ft_SIGINT(int signo)
{
	// ft_printf("signal:%d", signo);
	if (signo == SIGINT)
	{
		printf("\nYou pressed Ctrl+C\nminishell>");
		// ms_display_prompt(ms);
	}
}

void	ft_SIGQUIT(int signo)
{
	if (signo == SIGQUIT)
	{
		printf("\nYou pressed Ctrl+D\nminishell>");
	}
}
