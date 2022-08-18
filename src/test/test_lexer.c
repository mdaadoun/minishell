#include "../../inc/minishell.h"

void test_lexer(t_minishell *ms, int debug)
{
    if (debug == TEST_LEXER_BUILTINS)
    {
        ft_printf("\n\e[1;32m===Test lexer builtin programs:===\e[m\n");
        test_builtins(ms, debug);
    }
	else if (debug == TEST_LEXER_QUOTES)
	{
		printf("\n\e[1;32m===Testing quotes lexer:===\e[m\n");
		test_quotes(ms, debug);
	}
    else if (debug == TEST_LEXER_EXTERNALS)
    {
        ft_printf("\n\e[1;32m===Test lexer external programs:===\e[m\n");
        test_externals(ms, debug);
    }
    else if (debug == TEST_LEXER_ENV)
    {
        ft_printf("\n\e[1;32m===Test lexer env:===\e[m\n");
        test_env(ms, debug);
    }
    else if (debug == TEST_LEXER_PIPES)
    {
        ft_printf("\n\e[1;32m===Test lexer pipes:===\e[m\n");
        test_pipes(ms, debug);
    }
    else if (debug == TEST_LEXER_REDIRECTIONS)
    {
        ft_printf("\n\e[1;32m===Testing lexer redirections===\e[m\n");
        test_redirections(ms, debug);
    }
    else if (debug == TEST_LEXER_ARGUMENTS)
    {
        printf("\n\e[1;32m===Testing lexer arguments===\e[m\n");
        test_arguments(ms, debug);
    }
    else if (debug == TEST_LEXER  || debug == TEST_ALL)
    {
	    printf("\n\e[1;32m===Testing LEXER===\e[m\n");
		test_quotes(ms, debug);
        test_pipes(ms, debug);
        test_env(ms, debug);
        test_redirections(ms, debug);
        test_builtins(ms, debug);
        test_externals(ms, debug);
        test_arguments(ms, debug);
    }
}
