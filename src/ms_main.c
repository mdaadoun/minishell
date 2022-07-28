/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:07:09 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/07/28 14:07:11 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_signals(int signo)
{
	if (signo == SIGINT)
		printf("\nYou pressed Ctrl+C\n|-->");
}

int	main(int ac, char **av)
{
	char	*input;

	if (signal(SIGINT, handle_signals) == SIG_ERR)
		printf("Failed\n");
	while (1)
	{
		input = readline("|-->");
		if (!input)
			break;
		if (!ft_strncmp(input, "exit", 4))
		{
			free(input);
			break;
		}
		add_history(input);
		free(input);
	}
	(void)ac;
	(void)av;
	return (0);
}
