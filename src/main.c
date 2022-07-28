#include "../inc/minishell.h"

int	main(int ac, char **av)
{
	char	*test;
	int	count;

	count = 0;
	while (count < 10)
	{
		test = readline("|-->");
		printf("%s\n", test);
		free(test);
		count++;
	}
	(void)ac;
	(void)av;
	return (0);
}
