#include "../../inc/minishell.h"

void test_builtins(t_minishell *ms, int debug)
{
    printf("\e[1;31m===Testing lexer if first token is builtin command===\e[m \n");
    test_run_command(ms, "echo hello", debug);
    test_run_command(ms, "cd ..", debug);
    test_run_command(ms, "pwd hello", debug);
    test_run_command(ms, "export hello", debug);
    test_run_command(ms, "unset hello", debug);
    test_run_command(ms, "env hello", debug);
    test_run_command(ms, "exit hello", debug);
    test_run_command(ms, "history hello", debug);
}

void test_externals(t_minishell *ms, int debug)
{
    printf("\e[1;31m===Testing lexer if first token is external command===\e[m \n");
    test_run_command(ms, "test hello", debug);
    test_run_command(ms, "echo hello", debug);
    test_run_command(ms, "cat cat", debug);
    test_run_command(ms, "htop hello", debug);
    test_run_command(ms, "ls -l", debug);
	test_run_command(ms, "$PAGER test", debug);
	test_run_command(ms, "'$PAGER test'", debug);
	test_run_command(ms, "\"$PAGER test\"", debug);
	test_run_command(ms, "'$PAGER' test", debug);
	test_run_command(ms, "\"$PAGER\" test", debug);
}

void test_pipes(t_minishell *ms, int debug)
{
    ft_printf("\e[1;34mTest lexer pipes:\e[m\n");
    test_run_command(ms, "'hello' | hello | hello", debug);
    test_run_command(ms, "cat | | \"cat | cat\"", debug);
    test_run_command(ms, "||cd | '$home'", debug);
    test_run_command(ms, "'$home'cd | cd | cd", debug);
    test_run_command(ms, "|", debug);
    test_run_command(ms, "||||", debug);
    test_run_command(ms, "| | | |", debug);
    test_run_command(ms, "echo hi | cat | cat | cat | cat", debug);
    test_run_command(ms, "echo | cat | ls | cd | export a | export b", debug);
    test_run_command(ms, "echo echo cat | cat cat cat | ls ls cat | cd echo export | export cat cat | export export", debug);
    test_run_command(ms, "cat | \"cat | cat\"", debug);
    test_run_command(ms, "echo hi | 'cat' | cat | 'ls' | cat", debug);
}

void test_redirections(t_minishell *ms, int debug)
{
    ft_printf("\e[1;31m===Testing lexer redirections===\e[m\n");
    test_run_command(ms, "'>>'> > <", debug);
    test_run_command(ms, ">>> > <<", debug);
    test_run_command(ms, "> > <<", debug);
    test_run_command(ms, "> >> <<", debug);
}

void test_arguments(t_minishell *ms, int debug)
{
    printf("\e[1;31m===Testing lexer arguments===\e[m\n");
    test_run_command(ms, "cat hello -o adsld | asd", debug);
    test_run_command(ms, "echo -la rmasd | export -l asd", debug);
    test_run_command(ms, "ls hello test | cat cat", debug);
    test_run_command(ms, "cat -o | ls ls | cat cat cat -cat", debug);
}

void test_others(t_minishell *ms, int debug)
{
    printf("\e[1;31m===Testing lexer others===\e[m\n");
    test_run_command(ms, "'hello' hello hello", debug);
    test_run_command(ms, "cat \"cat cat\"", debug);
    test_run_command(ms, "cd '$home'", debug);
    test_run_command(ms, "'$home'cd cd cd", debug);
}

void test_lexer(t_minishell *ms, int debug)
{
    if (debug == TEST_LEXER_BUILTINS)
        test_builtins(ms, debug);
    else if (debug == TEST_LEXER_EXTERNALS)
        test_externals(ms, debug);
    else if (debug == TEST_LEXER_PIPES)
        test_pipes(ms, debug);
    else if (debug == TEST_LEXER_REDIRECTIONS)
        test_redirections(ms, debug);
    else if (debug == TEST_LEXER_ARGUMENTS)
        test_arguments(ms, debug);
    else if (debug == TEST_LEXER  || debug == TEST_ALL)
    {
	    printf("\e[1;32m===Testing LEXER===\e[m\n");
        test_builtins(ms, debug);
        test_externals(ms, debug);
        test_pipes(ms, debug);
        test_redirections(ms, debug);
        test_arguments(ms, debug);
        test_others(ms, debug);
    }
}
