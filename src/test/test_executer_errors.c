#include "../../inc/minishell.h"

void test_executer_errors(t_minishell *ms, int debug)
{
    if (debug == TEST_EXECUTER_ERRORS_BUILTINS)
    {
        ft_printf("\n\e[1;34m===Testing processes errors builtins programs:===\e[m\n");
        test_builtins(ms, debug);
    }
    else if (debug == TEST_EXECUTER_ERRORS_EXTERNALS)
    {
        ft_printf("\n\e[1;34m===Testing processes errors externals programs:===\e[m\n");
        test_externals(ms, debug);
    }
	else if (debug == TEST_EXECUTER_ERRORS_QUOTES)
	{
		printf("\n\e[1;34m===Testing processes errors quotes:===\e[m\n");
		test_quotes(ms, debug);
	}
	else if (debug == TEST_EXECUTER_ERRORS_ENV)
	{
		printf("\n\e[1;34m===Testing processes errors env:===\e[m\n");
		test_env(ms, debug);
	}
	else if (debug == TEST_EXECUTER_ERRORS_PIPES)
	{
		printf("\e[1;34m===Testing processes errors pipes===\e[m\n");
		test_pipes(ms, debug);
	}
	else if (debug == TEST_EXECUTER_ERRORS_REDIRECTIONS)
	{
		printf("\e[1;34m===Testing processes errors redirections===\e[m\n");
		test_redirections(ms, debug);
	}
	else if (debug == TEST_EXECUTER_ERRORS_ARGUMENTS)
	{
		printf("\n\e[1;34m===Testing processes errors arguments:===\e[m\n");
		test_arguments(ms, debug);
	}
    else if (debug == TEST_EXECUTER_ERRORS  || debug == TEST_ALL)
    {
		printf("===Testing EXECUTER ERRORS===\n");
		test_quotes(ms, debug);
        test_pipes(ms, debug);
        test_env(ms, debug);
        test_redirections(ms, debug);
        test_builtins(ms, debug);
        test_externals(ms, debug);
        test_arguments(ms, debug);
	}
}
