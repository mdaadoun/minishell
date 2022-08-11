#include "../../inc/minishell.h"

void launch_lexer_command(t_minishell *ms)
{
    ft_printf("\e[1;34mTest with command:\e[m %s\n", ms->full_command);
    
    ms_parser(ms);
    ms_analyze_command(ms, ms->first_token);
    if (ms->first_token->type == TYPE_EXTERNAL_COMMAND)
        ft_printf("%s is a valid command of type %d (external).\n", ms->first_token->content, ms->first_token->type);
    if (ms->first_token->type == TYPE_BUILTIN_COMMAND)
        ft_printf("%s is a valid command of type %d (builtin).\n", ms->first_token->content, ms->first_token->type);
    else
        ft_printf("%s is not a valid command.\n", ms->first_token->content);

    test_display_tokens_types(ms);

	test_reset(ms);
}

void launch_lexer_pipe(t_minishell *ms)
{
    ft_printf("\e[1;34mTest lexer pipes:\e[m %s\n", ms->full_command);

    ms_parser(ms);
    ms_analyze_command(ms, ms->first_token);
    ms_analyze_pipes(ms);

    test_display_tokens_types(ms);

	test_reset(ms);
}

void launch_lexer_redirections(t_minishell *ms)
{
	printf("\e[1;31m===Testing lexer redirections===\e[m\n");
    ft_printf("\e[1;34mFull command:\e[m %s\n", ms->full_command);

    ms_parser(ms);
	ms_analyze_command(ms, ms->first_token);
	ms_analyze_pipes(ms);
	ms_analyze_redirections(ms);

    test_display_tokens_types(ms);

	test_reset(ms);
}

void launch_lexer_arguments(t_minishell *ms)
{
	printf("\e[1;31m===Testing lexer arguments===\e[m\n");
    ft_printf("\e[1;34mFull command:\e[m %s\n", ms->full_command);

    ms_parser(ms);
	ms_analyze_command(ms, ms->first_token);
	ms_analyze_pipes(ms);
	ms_analyze_redirections(ms);
	ms_analyze_arguments(ms);

    test_display_tokens_types(ms);

	test_reset(ms);
}

void test_builtins(t_minishell *ms)
{
	printf("===Testing builtins lexer===\n");
    test_run_command(ms, "echo hello", &launch_lexer_command);
    test_run_command(ms, "cd ..", &launch_lexer_command);
    test_run_command(ms, "pwd hello", &launch_lexer_command);
    test_run_command(ms, "export hello", &launch_lexer_command);
    test_run_command(ms, "unset hello", &launch_lexer_command);
    test_run_command(ms, "env hello", &launch_lexer_command);
    test_run_command(ms, "exit hello", &launch_lexer_command);
    test_run_command(ms, "history hello", &launch_lexer_command);
}

void test_externals(t_minishell *ms)
{
	printf("===Testing external lexer===\n");
    test_run_command(ms, "test hello", &launch_lexer_command);
    test_run_command(ms, "echo hello", &launch_lexer_command);
    test_run_command(ms, "cat cat", &launch_lexer_command);
    test_run_command(ms, "htop hello", &launch_lexer_command);
    test_run_command(ms, "ls -l", &launch_lexer_command);
}

void test_pipes(t_minishell *ms)
{
	printf("===Testing pipes lexer===\n");
    test_run_command(ms, "'hello' | hello | hello", &launch_lexer_pipe);
    test_run_command(ms, "cat | | \"cat | cat\"", &launch_lexer_pipe);
    test_run_command(ms, "||cd | '$home'", &launch_lexer_pipe);
    test_run_command(ms, "'$home'cd | cd | cd", &launch_lexer_pipe);
    test_run_command(ms, "|", &launch_lexer_pipe);
    test_run_command(ms, "||||", &launch_lexer_pipe);
    test_run_command(ms, "| | | |", &launch_lexer_pipe);
    test_run_command(ms, "echo hi | cat | cat | cat | cat", &launch_lexer_pipe);
}

void test_pipes_and_commands(t_minishell *ms)
{
	printf("===Testing pipes lexer===\n");
    test_run_command(ms, "echo | cat | ls | cd | export a | export b", &launch_lexer_pipe);
    test_run_command(ms, "echo echo cat | cat cat cat | ls ls cat | cd echo export | export cat cat | export export", &launch_lexer_pipe);
    test_run_command(ms, "cat | \"cat | cat\"", &launch_lexer_pipe);
    test_run_command(ms, "echo hi | 'cat' | cat | 'ls' | cat", &launch_lexer_pipe);
}

void test_others(t_minishell *ms)
{
    test_run_command(ms, "'hello' hello hello", &launch_lexer_arguments);
    test_run_command(ms, "cat \"cat cat\"", &launch_lexer_arguments);
    test_run_command(ms, "cd '$home'", &launch_lexer_arguments);
    test_run_command(ms, "'$home'cd cd cd", &launch_lexer_arguments);
}

void test_redirections(t_minishell *ms)
{
    test_run_command(ms, "'>>'> > <", &launch_lexer_redirections);
    test_run_command(ms, ">>> > <<", &launch_lexer_redirections);
    test_run_command(ms, "> > <<", &launch_lexer_redirections);
    test_run_command(ms, "> >> <<", &launch_lexer_redirections);
}

void test_arguments(t_minishell *ms)
{
    test_run_command(ms, "cat hello -o adsld | asd", &launch_lexer_arguments);
    test_run_command(ms, "echo -la rmasd | export -l asd", &launch_lexer_arguments);
    test_run_command(ms, "ls hello test | cat cat", &launch_lexer_arguments);
    test_run_command(ms, "cat -o | ls ls | cat cat cat -cat", &launch_lexer_arguments);
}

void test_lexer(t_minishell *ms, int debug)
{
    if (debug == TEST_LEXER_BUILTINS)
        test_builtins(ms);
    if (debug == TEST_LEXER_EXTERNALS)
        test_externals(ms);
    if (debug == TEST_LEXER_PIPES)
    {
        test_pipes(ms);
        test_pipes_and_commands(ms);
    }
    if (debug == TEST_LEXER_REDIRECTIONS)
        test_redirections(ms);
    if (debug == TEST_LEXER_ARGUMENTS)
        test_arguments(ms);
    if (debug == TEST_LEXER  || debug == TEST_ALL)
    {
	    printf("===Testing LEXER===\n");
        test_builtins(ms);
        test_externals(ms);
        test_pipes(ms);
        test_pipes_and_commands(ms);
        test_redirections(ms);
        test_arguments(ms);
        test_others(ms);
    }
}
