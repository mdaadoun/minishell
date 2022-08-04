#include "../../inc/minishell.h"

void launch_lexer_command(t_minishell *ms)
{
    ft_printf("TEST LEXER with command: %s\n", ms->full_line);
    ms_parser(ms);
    if (ms_is_valid_command(ms))
    {

    }
    ft_printf("The tokens are: \n");
    display_tokens(ms);
    ms_free_all_tokens(ms);
    ft_printf("\n");
}

void test_builtins(t_minishell *ms)
{
    ms->full_line = ft_strdup("echo hello");
    launch_lexer_command(ms);
    ms->full_line = ft_strdup("cd ..");
    launch_lexer_command(ms);
    ms->full_line = ft_strdup("pwd hello");
    launch_lexer_command(ms);
    ms->full_line = ft_strdup("export hello");
    launch_lexer_command(ms);
    ms->full_line = ft_strdup("unset hello");
    launch_lexer_command(ms);
    ms->full_line = ft_strdup("env hello");
    launch_lexer_command(ms);
    ms->full_line = ft_strdup("exit hello");
    launch_lexer_command(ms);
    ms->full_line = ft_strdup("history hello");
    launch_lexer_command(ms);
}

void test_externals(t_minishell *ms)
{
    ms->full_line = ft_strdup("test hello");
    launch_lexer_command(ms);
    ms->full_line = ft_strdup("echo hello");
    launch_lexer_command(ms);
    ms->full_line = ft_strdup("cat cat");
    launch_lexer_command(ms);
    ms->full_line = ft_strdup("htop hello");
    launch_lexer_command(ms);
    ms->full_line = ft_strdup("ls -l");
    launch_lexer_command(ms);
}

void test_others(t_minishell *ms)
{
    ms->full_line = ft_strdup("'hello' hello hello");
    launch_lexer_command(ms);
    ms->full_line = ft_strdup("cat \"cat cat\"");
    launch_lexer_command(ms);
    ms->full_line = ft_strdup("cd '$home'");
    launch_lexer_command(ms);
    ms->full_line = ft_strdup("'$home'cd cd cd");
    launch_lexer_command(ms);
}

void test_lexer(t_minishell *ms, int debug)
{
    if (debug == TEST_LEXER_BUILTINS)
        test_builtins(ms);
    if (debug == TEST_LEXER_EXTERNALS)
        test_externals(ms);
    // if (debug == TEST_LEXER_PIPES)
    //     test_pipes(ms);
    if (debug == TEST_LEXER)
    {
        test_builtins(ms);
        test_externals(ms);
        // test_pipes(ms);
        test_others(ms);
    }
}
