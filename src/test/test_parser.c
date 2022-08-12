#include "../../inc/minishell.h"

static void	test_parsing_quote(t_minishell *ms, int debug)
{
	printf("\e[1;31m===Testing quotes parser===\n");
	test_run_command(ms, "'echo lol'", debug);
	test_run_command(ms, "'hello' hello hello", debug);
    test_run_command(ms, "'hello'", debug);
    test_run_command(ms, "'he\"l\"lo'", debug);
    test_run_command(ms, "test'123\"456\"123'test", debug);
    test_run_command(ms, "test\"123'456'123\"test", debug);
    test_run_command(ms, "test\"123'456'123\"test", debug);
}

static void	test_parsing_env(t_minishell *ms, int debug)
{
	printf("\e[1;31m===Testing env parser===\e[m\n");
	test_run_command(ms, "echo $PAGER", debug);
	test_run_command(ms, "echo $BA", debug);
	test_run_command(ms, "$BA", debug);
	test_run_command(ms, "$BA echo", debug);
	test_run_command(ms, "export a=$BA", debug);
	test_run_command(ms, "echo \"$LOGNAME\"", debug);
	test_run_command(ms, "echo \'$LOGNAME\'", debug);
	test_run_command(ms, "echo test     \\    test", debug);
	test_run_command(ms, "echo \"test", debug);
	test_run_command(ms, "echo $TEST", debug);
	test_run_command(ms, "echo \"$TEST\"", debug);
	test_run_command(ms, "\"echo '$TEST'\"", debug);
	test_run_command(ms, "echo \"$TEST$TEST$TEST\"", debug);
	test_run_command(ms, "echo \"$TEST$TEST=lol$TEST\"", debug);
	test_run_command(ms, "echo \"   $TEST lol $TEST\"", debug);
	test_run_command(ms, "echo $TEST$TEST$TEST", debug);
	test_run_command(ms, "echo $TEST$TEST=lol$TEST""lol", debug);
	test_run_command(ms, "echo    $TEST lol $TEST", debug);
	test_run_command(ms, "echo test "" test "" test", debug);
	test_run_command(ms, "echo \"\\$TEST\"", debug);
	test_run_command(ms, "echo \"$=TEST\"", debug);
	test_run_command(ms, "echo \"$\"", debug);
	test_run_command(ms, "echo \"$?TEST\"", debug);
	test_run_command(ms, "echo $TEST $TEST", debug);
	test_run_command(ms, "echo \"$1TEST\"", debug);
	test_run_command(ms, "echo \"$T1TEST\"", debug);
	//  'export ='
	//  'export 1TEST= ; env | sort | grep -v SHLVL | grep -v _='
	//  'export TEST ; export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD'
	//  'export ""="" ;  env | sort | grep -v SHLVL | grep -v _='
	//  'export TES=T="" ; env | sort | grep -v SHLVL | grep -v _='
	//  'export TE+S=T="" ; env | sort | grep -v SHLVL | grep -v _='
	//  'export TEST=LOL ; echo $TEST ; env | sort | grep -v SHLVL | grep -v _='
	//  'export TEST=LOL ; echo $TEST$TEST$TEST=lol$TEST'
	//  'export TEST=LOL; export TEST+=LOL ; echo $TEST ; env | sort | grep -v SHLVL | grep -v _='
	//  'env | sort | grep -v SHLVL | grep -v _='
	//  'export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD'
	//  'export TEST="ls       -l     - a" ; echo $TEST ; $LS ; ' 'env | sort | grep -v SHLVL | grep -v _='
}

static void	test_parsing_pipe(t_minishell *ms, int debug)
{
	printf("\e[1;31m===Testing pipe parser===\e[m\n");
	test_run_command(ms, "cat Makefile|wc -l", debug);
    test_run_command(ms, "cat Makefile | wc -l", debug);
    test_run_command(ms, "cat 'Makefile|wc' -l", debug);
    test_run_command(ms, "|wc -l", debug);
    test_run_command(ms, "| | | | |", debug);
}

static void	test_parsing_redirections(t_minishell *ms, int debug)
{
	printf("\e[1;31m===Testing redirection parser===\e[m\n");
	test_run_command(ms, "echo test > ls ; cat ls", debug);
	test_run_command(ms, "echo test > ls >> ls >> ls ; echo test >> ls; cat ls", debug);
	test_run_command(ms, "> lol echo test lol; cat lol", debug);
	test_run_command(ms, ">lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test", debug);
	test_run_command(ms, "cat < ls", debug);
	test_run_command(ms, "cat < ls > ls", debug);
}

void test_parser(t_minishell *ms, int debug)
{
	if (debug == TEST_PARSER_QUOTES)
		test_parsing_quote(ms, debug);
	if (debug == TEST_PARSER_ENV)
		test_parsing_env(ms, debug);
	if (debug == TEST_PARSER_PIPES)
		test_parsing_pipe(ms, debug);
	if (debug == TEST_PARSER_REDIRECTIONS)
		test_parsing_redirections(ms, debug);
    if (debug == TEST_PARSER || debug == TEST_ALL)
    {
		printf("\e[1;32m===Testing PARSER===\e[m\n");
		test_parsing_quote(ms, debug);
		test_parsing_env(ms, debug);
		test_parsing_pipe(ms, debug);
		test_parsing_redirections(ms, debug);
	}
}
