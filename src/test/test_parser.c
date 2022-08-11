#include "../../inc/minishell.h"

void launch_parser(t_minishell *ms)
{
    ft_printf("\e[1;34mTest with command:\e[m %s\n", ms->full_command);
    ms_parser(ms);

    test_display_tokens(ms);

	test_reset(ms);
}

void	test_quote(t_minishell *ms)
{
	printf("===Testing quotes parser===\n");
	test_run_command(ms, "'echo lol'", &launch_parser);
	test_run_command(ms, "'hello' hello hello", &launch_parser);
    test_run_command(ms, "'hello'", &launch_parser);
    test_run_command(ms, "'he\"l\"lo'", &launch_parser);
    test_run_command(ms, "test'123\"456\"123'test", &launch_parser);
    test_run_command(ms, "test\"123'456'123\"test", &launch_parser);
}

void	test_env(t_minishell *ms)
{
	printf("===Testing env parser===\n");
	test_run_command(ms, "echo $PAGER", &launch_parser);
	test_run_command(ms, "echo $BA", &launch_parser);
	test_run_command(ms, "$BA", &launch_parser);
	test_run_command(ms, "$BA echo", &launch_parser);
	test_run_command(ms, "export a=$BA", &launch_parser);
	test_run_command(ms, "echo \"$LOGNAME\"", &launch_parser);
	test_run_command(ms, "echo \'$LOGNAME\'", &launch_parser);
}

void	test_pipe(t_minishell *ms)
{
	printf("===Testing pipe parser===\n");
	test_run_command(ms, "cat Makefile|wc -l", &launch_parser);
    test_run_command(ms, "cat Makefile | wc -l", &launch_parser);
    test_run_command(ms, "cat 'Makefile|wc' -l", &launch_parser);
    test_run_command(ms, "|wc -l", &launch_parser);
    test_run_command(ms, "| | | | |", &launch_parser);
}

void test_parser(t_minishell *ms, int debug)
{
	if (debug == TEST_PARSER_QUOTES)
		test_quote(ms);
	if (debug == TEST_PARSER_ENV)
		test_env(ms);
	if (debug == TEST_PARSER_PIPES)
		test_pipe(ms);
    if (debug == TEST_PARSER || debug == TEST_ALL)
    {
	    printf("===Testing PARSER===\n");
		test_quote(ms);
		test_env(ms);
		test_pipe(ms);
	}
}
