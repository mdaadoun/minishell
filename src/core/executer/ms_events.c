/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:00:10 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/02 16:01:38 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"


void	handle_signals(int signo)
{
	// ft_printf("signal:%d", signo);
	if (signo == SIGINT)
	{
		printf("\nYou pressed Ctrl+C\nminishell>");
		// ms_display_prompt(ms);
	}
}
