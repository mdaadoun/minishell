#include "../inc/minishell.h"
#include <errno.h>
#include <error.h>
#include <getopt.h>
#include <signal.h>

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
		free(input);
	}
	(void)ac;
	(void)av;
	return (0);
}
