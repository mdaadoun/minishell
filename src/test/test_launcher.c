#include "../../inc/minishell.h"

void test_launcher(t_minishell *ms, int debug)
{
	bool next;

	next = true;
	ms_parser(ms);
	if (debug == TEST_PARSER || debug == TEST_PARSER_QUOTES \
	|| debug == TEST_PARSER_ENV || debug == TEST_PARSER_PIPES \
	|| debug == TEST_PARSER_REDIRECTIONS || debug == TEST_PARSER_ARGUMENTS \
	|| debug == TEST_PARSER_BUILTINS || debug == TEST_PARSER_EXTERNALS)
	{
		test_display_tokens(ms);
		next = false;
	}
	if (next)
	{
		ms_analyzer(ms);
		if (debug == TEST_ANALYZER_BUILTINS || debug == TEST_ANALYZER_EXTERNALS \
		|| debug == TEST_ANALYZER_ARGUMENTS || debug == TEST_ANALYZER || debug == TEST_ANALYZER_QUOTES \
		|| debug == TEST_ANALYZER_ENV || debug == TEST_ANALYZER_PIPES || debug == TEST_ANALYZER_REDIRECTIONS)
		{
			test_display_tokens_types(ms);
			next = false;
		}
	}
	if (next)
	{
    	ms_build_processes(ms);
		if (debug == TEST_EXECUTER_BUILD || debug == TEST_EXECUTER_BUILD_QUOTES \
		|| debug == TEST_EXECUTER_BUILD_ENV || debug == TEST_EXECUTER_BUILD_PIPES \
		|| debug == TEST_EXECUTER_BUILD_REDIRECTIONS || debug == TEST_EXECUTER_BUILD_ARGUMENTS \
		|| debug == TEST_EXECUTER_BUILD_BUILTINS || debug == TEST_EXECUTER_BUILD_EXTERNALS)
		{
    		test_display_processes(ms);
			next = false;
		}
	}
	if (next)
	{
    	ms_checking_for_errors(ms);
		if (debug == TEST_EXECUTER_ERRORS || debug == TEST_EXECUTER_ERRORS_QUOTES \
		|| debug == TEST_EXECUTER_ERRORS_ENV || debug == TEST_EXECUTER_ERRORS_PIPES \
		|| debug == TEST_EXECUTER_ERRORS_REDIRECTIONS || debug == TEST_EXECUTER_ERRORS_ARGUMENTS \
		|| debug == TEST_EXECUTER_ERRORS_BUILTINS || debug == TEST_EXECUTER_ERRORS_EXTERNALS)
		{
    		test_display_errors(ms);
			next = false;
		}
	}
	if (next)
	{
		if (debug == TEST_EXECUTER_REDIRECTIONS || debug == TEST_EXECUTER_REDIRECTIONS_QUOTES \
		|| debug == TEST_EXECUTER_REDIRECTIONS_PIPES || debug == TEST_EXECUTER_REDIRECTIONS_ENV \
		|| debug == TEST_EXECUTER_REDIRECTIONS_ARGUMENTS || debug == TEST_EXECUTER_REDIRECTIONS_REDIRECTIONS \
		|| debug == TEST_EXECUTER_REDIRECTIONS_BUILTINS || debug == TEST_EXECUTER_REDIRECTIONS_EXTERNALS)
		{
    		test_display_redirections(ms);
			next = false;
		}
	}
}
