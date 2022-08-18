#include "../../inc/minishell.h"

void test_launcher(t_minishell *ms, int debug)
{
	bool next;

	next = true;
	ms_parser(ms);
	if (debug == TEST_PARSER || debug == TEST_PARSER_QUOTES \
	|| debug == TEST_PARSER_ENV || debug == TEST_PARSER_PIPES \
	|| debug == TEST_PARSER_REDIRECTIONS || debug == TEST_PARSER_ARGUMENTS)
	{
		test_display_tokens(ms);
		next = false;
	}
	if (next)
	{
		if (debug == TEST_LEXER_BUILTINS || debug == TEST_LEXER_EXTERNALS)
		{
			ms_analyze_command(ms, ms->first_token);
			if (ms->first_token->type == TYPE_EXTERNAL_COMMAND)
				ft_printf("%s is a valid command of type %d (external).\n", ms->first_token->content, ms->first_token->type);
			else if (ms->first_token->type == TYPE_BUILTIN_COMMAND)
				ft_printf("%s is a valid command of type %d (builtin).\n", ms->first_token->content, ms->first_token->type);
			else
				ft_printf("%s is not a valid command.\n", ms->first_token->content);
			test_display_tokens_types(ms);
			next = false;
		}
	}
	if (next)
	{
		if (debug == TEST_LEXER_PIPES)
		{
			ms_analyze_command(ms, ms->first_token);
    		ms_analyze_pipes(ms);
			test_display_tokens_types(ms);
			next = false;
		}
	}
	if (next)
	{
		if (debug == TEST_LEXER_REDIRECTIONS)
		{
			ms_analyze_command(ms, ms->first_token);
    		ms_analyze_pipes(ms);
    		ms_analyze_redirections(ms);
			test_display_tokens_types(ms);
			next = false;
		}
	}
	if (next)
	{
		ms_lexer(ms);
		if (debug == TEST_LEXER_ARGUMENTS || debug == TEST_LEXER)
		{
			test_display_tokens_types(ms);
			next = false;
		}
	}
	if (next)
	{
    	ms_build_processes(ms);
		if (debug == TEST_EXECUTER_PROCESSES_BUILD)
		{
    		test_display_processes(ms);
			next = false;
		}
	}
	if (next)
	{
    	ms_checking_for_errors(ms);
		if (debug == TEST_EXECUTER_PROCESSES_ERROR)
		{
    		test_display_errors(ms);
			next = false;
		}
	}
	if (next)
	{
		if (debug == TEST_EXECUTER_PROCESSES_PIPE)
		{
			ft_printf("TEST_EXECUTER_PROCESSES_PIPE ok\n");
			next = false;
		}
	}
	if (next)
	{
		if (debug == TEST_EXECUTER_PROCESSES_REDIRECTION)
		{
			ft_printf("TEST_EXECUTER_PROCESSES_REDIRECTION ok\n");
			next = false;
		}
	}
	if (next)
	{
		if (debug == TEST_EXECUTER || debug == TEST_EXECUTER_PROCESSES_EXECV)
		{
			next = false;
		}
	}
}
