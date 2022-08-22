/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:28:29 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/22 14:11:50 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	cancel_process(int signo)
{
	char	*buf;
	char 	*cwd_path;

	buf = (char *)ft_calloc(sizeof(char), 1024);
	cwd_path = getcwd(buf, 1024);
	if (signo == SIGINT)
		printf("\n\e[1;38m%s\e[m>", cwd_path);
	if (signo == SIGQUIT)
		return ;
	// free(buf);
	free(cwd_path);
}

void	ms_initialize_signals(void)
{
	if (signal(SIGINT, cancel_process) == SIG_ERR)
		ft_printf("Failed SIGINT\n");
	if (signal(SIGQUIT, cancel_process) == SIG_ERR)
		ft_printf("Failed SIGQUIT\n");
}
