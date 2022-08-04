#include "../../inc/minishell.h"

void launch_lexer_command(t_minishell *ms)
{
    ft_printf("\e[1;34mTest with command:\e[m %s\n", ms->full_line);
    ms_parser(ms);
    ms_analyse_command(ms, ms->first_token);
    if (ms->first_token->type == TYPE_EXTERNAL_COMMAND)
        ft_printf("%s is a valid command of type %d (external).\n", ms->first_token->content, ms->first_token->type);
    if (ms->first_token->type == TYPE_BUILTIN_COMMAND)
        ft_printf("%s is a valid command of type %d (builtin).\n", ms->first_token->content, ms->first_token->type);
    else
        ft_printf("%s is not a valid command.\n", ms->first_token->content);
    ft_printf("\e[1;34mThe tokens are:\e[m \n");
    display_tokens(ms);
    ms_free_all_tokens(ms);
    ft_printf("\n");
}

void test_builtins(t_minishell *ms)
{
	printf("===Testing builtins lexer===\n");
    ms->full_line = ft_strdup("echo hello");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("cd ..");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("pwd hello");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("export hello");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("unset hello");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("env hello");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("exit hello");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("history hello");
    launch_lexer_command(ms);
	free(ms->full_line);
}

void test_externals(t_minishell *ms)
{
	printf("===Testing external lexer===\n");
    ms->full_line = ft_strdup("test hello");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("echo hello");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("cat cat");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("htop hello");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("ls -l");
    launch_lexer_command(ms);
	free(ms->full_line);
}

void test_pipes(t_minishell *ms)
{
	printf("===Testing pipes lexer===\n");
    ms->full_line = ft_strdup("'hello' | hello | hello");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("cat | | \"cat | cat\"");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("||cd | '$home'");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("'$home'cd | cd | cd");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("|");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("||||");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("echo hi | cat | cat | cat | cat");
    launch_lexer_command(ms);
	free(ms->full_line);
}

void test_others(t_minishell *ms)
{
    ms->full_line = ft_strdup("'hello' hello hello");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("cat \"cat cat\"");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("cd '$home'");
    launch_lexer_command(ms);
	free(ms->full_line);
    ms->full_line = ft_strdup("'$home'cd cd cd");
    launch_lexer_command(ms);
	free(ms->full_line);
}

void test_lexer(t_minishell *ms, int debug)
{
    if (debug == TEST_LEXER_BUILTINS)
        test_builtins(ms);
    if (debug == TEST_LEXER_EXTERNALS)
        test_externals(ms);
    if (debug == TEST_LEXER_PIPES)
        test_pipes(ms);
    if (debug == TEST_LEXER)
    {
	    printf("===Testing LEXER===\n");
        test_builtins(ms);
        test_externals(ms);
        test_pipes(ms);
        test_others(ms);
    }
}
