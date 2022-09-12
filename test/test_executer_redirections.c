#include "../../inc/minishell.h"

void test_executer_redirections(t_minishell *ms, int debug)
{
    if (debug == TEST_EXECUTER_REDIRECTIONS_BUILTINS)
    {
        ft_printf("\n\e[1;34m===Testing processes REDIRECTIONS builtins programs:===\e[m\n");
        test_builtins(ms, debug);
    }
    else if (debug == TEST_EXECUTER_REDIRECTIONS_EXTERNALS)
    {
        ft_printf("\n\e[1;34m===Testing processes REDIRECTIONS externals programs:===\e[m\n");
        test_externals(ms, debug);
    }
	else if (debug == TEST_EXECUTER_REDIRECTIONS_QUOTES)
	{
		printf("\n\e[1;34m===Testing processes REDIRECTIONS quotes:===\e[m\n");
		test_quotes(ms, debug);
	}
	else if (debug == TEST_EXECUTER_REDIRECTIONS_ENV)
	{
		printf("\n\e[1;34m===Testing processes REDIRECTIONS env:===\e[m\n");
		test_env(ms, debug);
	}
	else if (debug == TEST_EXECUTER_REDIRECTIONS_PIPES)
	{
		printf("\e[1;34m===Testing processes REDIRECTIONS pipes===\e[m\n");
		test_pipes(ms, debug);
	}
	else if (debug == TEST_EXECUTER_REDIRECTIONS_REDIRECTIONS)
	{
		printf("\e[1;34m===Testing processes REDIRECTIONS redirections===\e[m\n");
		test_redirections(ms, debug);
	}
	else if (debug == TEST_EXECUTER_REDIRECTIONS_ARGUMENTS)
	{
		printf("\n\e[1;34m===Testing processes REDIRECTIONS arguments:===\e[m\n");
		test_arguments(ms, debug);
	}
    else if (debug == TEST_EXECUTER_REDIRECTIONS  || debug == TEST_ALL)
    {
		printf("===Testing EXECUTER REDIRECTIONS===\n");
		test_quotes(ms, debug);
        test_pipes(ms, debug);
        test_env(ms, debug);
        test_redirections(ms, debug);
        test_builtins(ms, debug);
        test_externals(ms, debug);
        test_arguments(ms, debug);
	}
}
