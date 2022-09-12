#include "../../inc/minishell.h"

void test_executer_build(t_minishell *ms, int debug)
{
    if (debug == TEST_EXECUTER_BUILD_BUILTINS)
    {
        ft_printf("\n\e[1;33m===Testing processes build builtins programs:===\e[m\n");
        test_builtins(ms, debug);
    }
    else if (debug == TEST_EXECUTER_BUILD_EXTERNALS)
    {
        ft_printf("\n\e[1;33m===Testing processes build externals programs:===\e[m\n");
        test_externals(ms, debug);
    }
	else if (debug == TEST_EXECUTER_BUILD_QUOTES)
	{
		printf("\n\e[1;33m===Testing processes build quotes:===\e[m\n");
		test_quotes(ms, debug);
	}
	else if (debug == TEST_EXECUTER_BUILD_ENV)
	{
		printf("\n\e[1;33m===Testing processes build env:===\e[m\n");
		test_env(ms, debug);
	}
	else if (debug == TEST_EXECUTER_BUILD_PIPES)
	{
		printf("\e[1;33m===Testing processes build pipes===\e[m\n");
		test_pipes(ms, debug);
	}
	else if (debug == TEST_EXECUTER_BUILD_REDIRECTIONS)
	{
		printf("\e[1;33m===Testing processes build redirections===\e[m\n");
		test_redirections(ms, debug);
	}
	else if (debug == TEST_EXECUTER_BUILD_ARGUMENTS)
	{
		printf("\n\e[1;33m===Testing processes build arguments:===\e[m\n");
		test_arguments(ms, debug);
	}
    else if (debug == TEST_EXECUTER_BUILD  || debug == TEST_ALL)
    {
		printf("===Testing EXECUTER BUILD===\n");
		test_quotes(ms, debug);
        test_pipes(ms, debug);
        test_env(ms, debug);
        test_redirections(ms, debug);
        test_builtins(ms, debug);
        test_externals(ms, debug);
        test_arguments(ms, debug);
	}
}
