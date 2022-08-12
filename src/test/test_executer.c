#include "../../inc/minishell.h"

void launch_executer_build(t_minishell *ms)
{

    ft_printf("\e[1;34mTest with command:\e[m %s\n", ms->full_command);
    ms_parser(ms);
	ms_lexer(ms);
    ms_build_processes(ms);

    test_display_tokens_types(ms);
    test_display_processes(ms);
	
	test_reset(ms);
}

void launch_executer_errors(t_minishell *ms)
{
    ft_printf("\e[1;34mTest with command:\e[m %s\n", ms->full_command);
    
	ms_parser(ms);
	ms_lexer(ms);
    ms_build_processes(ms);
    ms_checking_for_errors(ms);

    test_display_tokens_types(ms);
    test_display_processes(ms);
    test_display_errors(ms);

	test_reset(ms);
}

static void	test_close_pipe(t_minishell *ms)
{
	t_process *proc;

	proc = ms->first_process;
	if (proc == ms->first_process)
	{
		close(proc->pipe_out);
		close(proc->next->pipe_in);
	}
	else if (proc->next == 0)
		return ;
	else
	{
		close(proc->pipe_out);
		close(proc->next->pipe_in);
	}
	proc = proc->next;
}

void launch_executer_pipe(t_minishell *ms)
{

    ft_printf("\e[1;34mTest with command:\e[m %s\n", ms->full_command);
    ms_parser(ms);
	ms_lexer(ms);
    ms_build_processes(ms);
	create_pipes(ms);

    test_display_tokens_types(ms);
    test_display_processes(ms);
	test_close_pipe(ms);
	test_reset(ms);
}

void	test_processes_build(t_minishell *ms)
{
	printf("\e[1;34m===Testing processes===\e[m\n");
	test_run_command(ms, "env hello", &launch_executer_build);
    test_run_command(ms, "env hello", &launch_executer_build);
    test_run_command(ms, "cat cat | 'cat' $hello", &launch_executer_build);
    test_run_command(ms, "env | echo | cat | ls", &launch_executer_build);
    test_run_command(ms, "test ||| test", &launch_executer_build);
    test_run_command(ms, "cat test | echo -o test | cd cd | echo | cat ", &launch_executer_build);
    test_run_command(ms, "sad | das| | asd| Asd| sda |", &launch_executer_build);
    test_run_command(ms, "'cat' | cat | \"cat\"", &launch_executer_build);
    test_run_command(ms, "     'cat    ' |  cat   | \"     cat     \"", &launch_executer_build);
    test_run_command(ms, "'$cat' | $cat | \"$cat\"", &launch_executer_build);
    test_run_command(ms, "cd | cd", &launch_executer_build);
}

void	test_processes_errors(t_minishell *ms)
{
	printf("\e[1;34m===Testing processes errors (BAD COMMANDS)===\e[m\n");
	test_run_command(ms, "asd | echo hello | eee eee", &launch_executer_errors);
	test_run_command(ms, "echo hello", &launch_executer_errors);
	test_run_command(ms, "echo test | asd hello | eee eee | echo hello | cat -e", &launch_executer_errors);
	printf("\e[1;34m===Testing processes errors (SYNTAX PIPES)===\e[m\n");
}


void	test_processes_pipe(t_minishell *ms)
{
	printf("\e[1;34m===Testing processes pipe===\e[m\n");
	test_run_command(ms, "env | wc", &launch_executer_pipe);
	test_run_command(ms, "env | wc | wc -l", &launch_executer_pipe);
}

void	launch_executer_process(t_minishell *ms)
{
    ft_printf("\e[1;34mTest with command:\e[m %s\n", ms->full_command);
    ms_parser(ms);
	ms_lexer(ms);
	ms_executer(ms);
    test_display_tokens_types(ms);
    test_display_processes(ms);
	test_close_pipe(ms);
	test_reset(ms);
}

void	test_processes_execv(t_minishell *ms)
{
	printf("\e[1;34m===Testing process execv===\e[m\n");
	test_run_command(ms, "cat Makefile | wc -l", &launch_executer_process);
	test_run_command(ms, "cat Makefile | wc -l | wc -l", &launch_executer_process);
}

void test_executer(t_minishell *ms, int debug)
{
	if (debug == TEST_EXECUTER_PROCESSES_BUILD)
		test_processes_build(ms);
	else if (debug == TEST_EXECUTER_PROCESSES_ERROR)
		test_processes_errors(ms);
	else if (debug == TEST_EXECUTER_PROCESSES_PIPE)
		test_processes_pipe(ms);
	else if (debug == TEST_EXECUTER_PROCESSES_EXECV)
		test_processes_execv(ms);
    else if (debug == TEST_EXECUTER  || debug == TEST_ALL)
    {
	    printf("===Testing EXECUTER===\n");
		test_processes_build(ms);
		test_processes_errors(ms);
		test_processes_pipe(ms);
	}
}
