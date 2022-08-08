#include "../../inc/minishell.h"

void display_tokens(t_minishell *ms)
{
    t_token *token;

    token = ms->first_token;

    while (token)
    {
        ft_printf("Content: %s		Type: %d\n", token->content, token->type);
        token = token->next;
    }
}

void launch_parser(t_minishell *ms, char *line)
{

    ft_printf("\e[1;34mTest with command:\e[m %s\n", line);
    ms_parser(ms);
    ft_printf("\e[1;34mThe tokens are:\e[m \n");
    display_tokens(ms);
    ms_free_all_tokens(ms);
    ft_printf("\n");
}

void	test_quote(t_minishell *ms)
{
	printf("===Testing quotes parser===\n");
	ms->full_line = ft_strdup("'echo lol'");
	launch_parser(ms, ms->full_line);
	free(ms->full_line);
	ms->full_line = ft_strdup("'hello' hello hello");
	launch_parser(ms, ms->full_line);
	free(ms->full_line);
    ms->full_line = ft_strdup("'hello'");
	launch_parser(ms, ms->full_line);
	free(ms->full_line);
    ms->full_line = ft_strdup("'he\"l\"lo'");
	launch_parser(ms, ms->full_line);
	free(ms->full_line);
    ms->full_line = ft_strdup("test'123\"456\"123'test");
	launch_parser(ms, ms->full_line);
	free(ms->full_line);
    ms->full_line = ft_strdup("test\"123'456'123\"test");
	launch_parser(ms, ms->full_line);
	free(ms->full_line);
}

void	test_env(t_minishell *ms)
{
	printf("===Testing env parser===\n");
	// ms->full_line = ft_strdup("echo $PAGER");
	// launch_parser(ms, ms->full_line);
	// free(ms->full_line);
	ms->full_line = ft_strdup("echo $BA");
	launch_parser(ms, ms->full_line);
	// free(ms->full_line);
	ms->full_line = ft_strdup("$BA echo $BA");
	launch_parser(ms, ms->full_line);
	// free(ms->full_line);
	ms->full_line = ft_strdup("$BA");
	launch_parser(ms, ms->full_line);
	// free(ms->full_line);
	ms->full_line = ft_strdup("$BA echo");
	launch_parser(ms, ms->full_line);
	// free(ms->full_line);
	ms->full_line = ft_strdup("echo $a");
	launch_parser(ms, ms->full_line);
	ms->full_line = ft_strdup("export a=$BA");
	launch_parser(ms, ms->full_line);
}

void	test_pipe(t_minishell *ms)
{
	printf("===Testing pipe parser===\n");
	ms->full_line = ft_strdup("cat Makefile|wc -l");
	launch_parser(ms, ms->full_line);
	free(ms->full_line);
    ms->full_line = ft_strdup("cat Makefile | wc -l");
	launch_parser(ms, ms->full_line);
	free(ms->full_line);
    ms->full_line = ft_strdup("cat 'Makefile|wc' -l");
	launch_parser(ms, ms->full_line);
	free(ms->full_line);
    ms->full_line = ft_strdup("|wc -l");
	launch_parser(ms, ms->full_line);
	free(ms->full_line);
    ms->full_line = ft_strdup("| | | | |");
	launch_parser(ms, ms->full_line);
	free(ms->full_line);
}

void test_parser(t_minishell *ms, int debug)
{
	if (debug == TEST_PARSER_QUOTES)
		test_quote(ms);
	if (debug == TEST_PARSER_ENV)
		test_env(ms);
	if (debug == TEST_PARSER_PIPES)
		test_pipe(ms);
    if (debug == TEST_PARSER)
    {
		test_quote(ms);
		test_env(ms);
		test_pipe(ms);
	}
}
