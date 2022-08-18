#include "../../inc/minishell.h"

void test_parser(t_minishell *ms, int debug)
{
    if (debug == TEST_LEXER_BUILTINS)
    {
        ft_printf("\n\e[1;34m===Testing builtins programs parser:===\e[m\n");
        test_builtins(ms, debug);
    }
    else if (debug == TEST_LEXER_EXTERNALS)
    {
        ft_printf("\n\e[1;34m===Testing externals programs parser:===\e[m\n");
        test_externals(ms, debug);
    }
	else if (debug == TEST_PARSER_QUOTES)
	{
		printf("\n\e[1;31m===Testing quotes parser:===\n");
		test_quotes(ms, debug);
	}
	else if (debug == TEST_PARSER_ENV)
	{
		printf("\n\e[1;31m===Testing env parser:===\e[m\n");
		test_env(ms, debug);
	}
	else if (debug == TEST_PARSER_PIPES)
	{
		printf("\n\e[1;31m===Testing pipes parser:===\e[m\n");
		test_pipes(ms, debug);
	}
	else if (debug == TEST_PARSER_REDIRECTIONS)
	{
		printf("\n\e[1;31m===Testing redirection parser:===\e[m\n");
		test_redirections(ms, debug);
	}
	else if (debug == TEST_PARSER_ARGUMENTS)
	{
		printf("\n\e[1;31m===Testing arguments parser:===\e[m\n");
		test_arguments(ms, debug);
	}
    else if (debug == TEST_PARSER || debug == TEST_ALL)
    {
		printf("\n\e[1;32m===Testing PARSER===\e[m\n");
		test_quotes(ms, debug);
		test_env(ms, debug);
		test_pipes(ms, debug);
		test_redirections(ms, debug);
		test_arguments(ms, debug);
	}
}
