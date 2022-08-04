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

    ft_printf("TEST PARSER with command: %s\n", line);
    ms_parser(ms);
    ft_printf("The tokens are: \n");
    display_tokens(ms);
    ms_free_all_tokens(ms);
    ft_printf("\n");
}

void test_parser(t_minishell *ms, int debug)
{
    if (debug == TEST_PARSER)
    {
        if (ms->full_line)
            launch_parser(ms, ms->full_line);
        ms->full_line = ft_strdup("'hello' hello hello");
        launch_parser(ms, ms->full_line);
        ms->full_line = ft_strdup("'hello'");
        launch_parser(ms, ms->full_line);
        ms->full_line = ft_strdup("'he\"l\"lo'");
        launch_parser(ms, ms->full_line);
        ms->full_line = ft_strdup("test'123\"456\"123'test");
        launch_parser(ms, ms->full_line);
        ms->full_line = ft_strdup("test\"123'456'123\"test");
        launch_parser(ms, ms->full_line);
        ms->full_line = ft_strdup(" test \" 123 ' 456 ' 123 \" test");
        launch_parser(ms, ms->full_line);
        ms->full_line = ft_strdup(" test .\". 123 ' 456 ' 123 .\". test");
        launch_parser(ms, ms->full_line);
        ms->full_line = ft_strdup("cat Makefile|wc -l");
        launch_parser(ms, ms->full_line);
        ms->full_line = ft_strdup("cat Makefile | wc -l");
        launch_parser(ms, ms->full_line);
        ms->full_line = ft_strdup("echo $PAGER");
        launch_parser(ms, ms->full_line);
        ms->full_line = ft_strdup("cat 'Makefile|wc' -l");
        launch_parser(ms, ms->full_line);
        ms->full_line = ft_strdup("|wc -l");
        launch_parser(ms, ms->full_line);
    }
}
