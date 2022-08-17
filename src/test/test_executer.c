#include "../../inc/minishell.h"


void	test_processes_build(t_minishell *ms, int debug)
{
	printf("\e[1;34m===Testing processes===\e[m\n");
	test_run_command(ms, "env hello", debug);
    test_run_command(ms, "env hello", debug);
    test_run_command(ms, "cat cat | 'cat' $hello", debug);
    test_run_command(ms, "env | echo | cat | ls", debug);
    test_run_command(ms, "test ||| test", debug);
    test_run_command(ms, "cat test | echo -o test | cd cd | echo | cat ", debug);
    test_run_command(ms, "sad | das| | asd| Asd| sda |", debug);
    test_run_command(ms, "'cat' | cat | \"cat\"", debug);
    test_run_command(ms, "     'cat    ' |  cat   | \"     cat     \"", debug);
    test_run_command(ms, "'$cat' | $cat | \"$cat\"", debug);
    test_run_command(ms, "cd | cd", debug);
}

void	test_processes_errors(t_minishell *ms, int debug)
{
	printf("\e[1;34m===Testing processes errors (BAD COMMANDS)===\e[m\n");
	test_run_command(ms, "asd | echo hello | eee eee", debug);
	test_run_command(ms, "echo hello", debug);
	test_run_command(ms, "echo test | asd hello | eee eee | echo hello | cat -e", debug);
	printf("\e[1;34m===Testing processes errors (SYNTAX ERROR)===\e[m\n");
	test_run_command(ms, ";; test", debug);
	test_run_command(ms, "| test", debug);
	test_run_command(ms, "echo > <", debug);
	test_run_command(ms, "echo hello | |", debug);
	test_run_command(ms, "<", debug);
}

void	test_processes_pipe(t_minishell *ms, int debug)
{
	test_run_command(ms, "env | wc", debug);
	test_run_command(ms, "env | wc | wc -l", debug);
}

void	test_processes_execv(t_minishell *ms, int debug)
{
	printf("\e[1;34m===Testing process execv===\e[m\n");
	test_run_command(ms, "cat Makefile | wc -l", debug);
	test_run_command(ms, "cat Makefile | wc -l | wc -l", debug);
	// 'echo testing multi ; echo "test 1 ; | and 2" ; cat tests/lorem.txt | grep Lorem'
}

void test_executer(t_minishell *ms, int debug)
{
	if (debug == TEST_EXECUTER_PROCESSES_BUILD)
		test_processes_build(ms, debug);
	else if (debug == TEST_EXECUTER_PROCESSES_ERROR)
		test_processes_errors(ms, debug);
	else if (debug == TEST_EXECUTER_PROCESSES_PIPE)
	{
		printf("\e[1;34m===Testing processes pipe===\e[m\n");
		test_processes_pipe(ms, debug);
	}
	else if (debug == TEST_EXECUTER_PROCESSES_REDIRECTION)
		test_processes_redirections(ms, debug);
	else if (debug == TEST_EXECUTER_PROCESSES_EXECV)
		test_processes_execv(ms, debug);
    else if (debug == TEST_EXECUTER  || debug == TEST_ALL)
    {
		printf("===Testing EXECUTER===\n");
		test_processes_build(ms, debug);
		test_processes_errors(ms, debug);
		test_processes_pipe(ms, debug);
		test_processes_execv(ms, debug);
	}
}
