#include "../../inc/minishell.h"

void launch_parser(t_minishell *ms)
{

    ft_printf("\e[1;34mTest with command:\e[m %s\n", ms->full_command);
    ms_parser(ms);
    ft_printf("\e[1;34mThe tokens are:\e[m \n");
    display_tokens(ms);
    ms_free_all_tokens(ms);
    ft_printf("\n");
}

void	test_quote(t_minishell *ms)
{
	printf("===Testing quotes parser===\n");
	ms->full_command = ft_strdup("'echo lol'");
	launch_parser(ms);
	free(ms->full_command);
	ms->full_command = ft_strdup("'hello' hello hello");
	launch_parser(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("'hello'");
	launch_parser(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("'he\"l\"lo'");
	launch_parser(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("test'123\"456\"123'test");
	launch_parser(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("test\"123'456'123\"test");
	launch_parser(ms);
	free(ms->full_command);
}

void	test_env(t_minishell *ms)
{
	printf("===Testing env parser===\n");
	ms->full_command = ft_strdup("echo $PAGER");
	launch_parser(ms);
	free(ms->full_command);
	ms->full_command = ft_strdup("echo $BA");
	launch_parser(ms);
	free(ms->full_command);
	ms->full_command = ft_strdup("$BA");
	launch_parser(ms);
	free(ms->full_command);
	ms->full_command = ft_strdup("$BA echo");
	launch_parser(ms);
	free(ms->full_command);
	ms->full_command = ft_strdup("export a=$BA");
	launch_parser(ms);
	free(ms->full_command);
	ms->full_command = ft_strdup("echo \"$LOGNAME\"");
	launch_parser(ms);
	free(ms->full_command);
	ms->full_command = ft_strdup("echo \'$LOGNAME\'");
	launch_parser(ms);
}

void	test_pipe(t_minishell *ms)
{
	printf("===Testing pipe parser===\n");
	ms->full_command = ft_strdup("cat Makefile|wc -l");
	launch_parser(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("cat Makefile | wc -l");
	launch_parser(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("cat 'Makefile|wc' -l");
	launch_parser(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("|wc -l");
	launch_parser(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("| | | | |");
	launch_parser(ms);
	free(ms->full_command);
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
