#include "../../inc/minishell.h"


void test_parser(t_minishell *ms, int debug)
{
	if (debug == TEST_PARSER_QUOTES)
	{
		printf("\e[1;31m===Testing quotes parser===\n");
		test_quotes(ms, debug);
	}
	if (debug == TEST_PARSER_ENV)
	{
		printf("\e[1;31m===Testing env parser===\e[m\n");
		test_env(ms, debug);
	}
	if (debug == TEST_PARSER_PIPES)
	{
		printf("\e[1;31m===Testing pipes parser===\e[m\n");
		test_pipes(ms, debug);
	}
	if (debug == TEST_PARSER_REDIRECTIONS)
	{
		printf("\e[1;31m===Testing redirection parser===\e[m\n");
		test_redirections(ms, debug);
	}
	if (debug == TEST_PARSER_ARGUMENTS)
	{
		printf("\e[1;31m===Testing arguments parser===\e[m\n");
		test_arguments(ms, debug);
	}
    if (debug == TEST_PARSER || debug == TEST_ALL)
    {
		printf("\e[1;32m===Testing PARSER===\e[m\n");
		test_quotes(ms, debug);
		test_env(ms, debug);
		test_pipes(ms, debug);
		test_redirections(ms, debug);
		test_arguments(ms, debug);
	}
}
