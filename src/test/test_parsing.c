#include "../../inc/minishell.h"

void display_tokens(t_minishell *ms)
{
    t_token *token;

    token = ms->first_token;

    while (token)
    {
        ft_printf("%s\n", token->content);
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

void test_parser(t_minishell *ms)
{
    if (ms->line)
        launch_parser(ms, ms->line);
    ms->line = "'hello' hello hello";
    launch_parser(ms, ms->line);
    ms->line = "'hello'";
    launch_parser(ms, ms->line);
    ms->line = "'he\"l\"lo'";
    launch_parser(ms, ms->line);
}
