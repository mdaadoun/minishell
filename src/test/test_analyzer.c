#include "../../inc/minishell.h"

void test_analyzer(t_minishell *ms, int debug)
{
    if (debug == TEST_ANALYZER_BUILTINS)
    {
        ft_printf("\n\e[1;32m===Test analyzer builtin programs:===\e[m\n");
        test_builtins(ms, debug);
    }
	else if (debug == TEST_ANALYZER_QUOTES)
	{
		printf("\n\e[1;32m===Testing quotes analyzer:===\e[m\n");
		test_quotes(ms, debug);
	}
    else if (debug == TEST_ANALYZER_EXTERNALS)
    {
        ft_printf("\n\e[1;32m===Test analyzer external programs:===\e[m\n");
        test_externals(ms, debug);
    }
    else if (debug == TEST_ANALYZER_ENV)
    {
        ft_printf("\n\e[1;32m===Test analyzer env:===\e[m\n");
        test_env(ms, debug);
    }
    else if (debug == TEST_ANALYZER_PIPES)
    {
        ft_printf("\n\e[1;32m===Test analyzer pipes:===\e[m\n");
        test_pipes(ms, debug);
    }
    else if (debug == TEST_ANALYZER_REDIRECTIONS)
    {
        ft_printf("\n\e[1;32m===Testing analyzer redirections===\e[m\n");
        test_redirections(ms, debug);
    }
    else if (debug == TEST_ANALYZER_ARGUMENTS)
    {
        printf("\n\e[1;32m===Testing analyzer arguments===\e[m\n");
        test_arguments(ms, debug);
    }
    else if (debug == TEST_ANALYZER  || debug == TEST_ALL)
    {
	    printf("\n\e[1;32m===Testing analyzer===\e[m\n");
		test_quotes(ms, debug);
        test_pipes(ms, debug);
        test_env(ms, debug);
        test_redirections(ms, debug);
        test_builtins(ms, debug);
        test_externals(ms, debug);
        test_arguments(ms, debug);
    }
}
