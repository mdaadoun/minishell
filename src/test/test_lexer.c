#include "../../inc/minishell.h"


void launch_lexer(t_minishell *ms)
{
    ft_printf("TEST LEXER with command: %s\n", ms->full_line);
    ms_parser(ms);
    ms_lexer(ms);
    ft_printf("The tokens are: \n");
    display_tokens(ms);
    ms_free_all_tokens(ms);
    ft_printf("\n");
}

void test_lexer(t_minishell *ms)
{
    if (ft_strlen(ms->full_line))
        launch_lexer(ms);
    ms->full_line = ft_strdup("'hello' hello hello");
    launch_lexer(ms);
    ms->full_line = ft_strdup("echo hello");
    launch_lexer(ms);
    ms->full_line = ft_strdup("cat \"cat cat\"");
    launch_lexer(ms);
    ms->full_line = ft_strdup("cd '$home'");
    launch_lexer(ms);
}
