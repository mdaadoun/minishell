#include "../../inc/minishell.h"

void launch_executer_build(t_minishell *ms)
{

    ft_printf("\e[1;34mTest with command:\e[m %s\n", ms->full_command);
    ms_parser(ms);
	ms_lexer(ms);
    ft_printf("\e[1;34mThe tokens are:\e[m \n");
    display_tokens_types(ms);
    ms_build_processes(ms);
    ft_printf("\e[1;34mThe processes are:\e[m \n");
    display_processes(ms);
    ms_free_all_tokens(ms);
    ms_free_all_processes(ms);
    ft_printf("\n");
}

void launch_executer_errors(t_minishell *ms)
{
    ft_printf("\e[1;34mTest with command:\e[m %s\n", ms->full_command);
    ms_parser(ms);
	ms_lexer(ms);
    ms_build_processes(ms);
    ms_checking_for_errors(ms);
    display_tokens_types(ms);
    display_processes(ms);
    test_display_errors(ms);
    ms_free_all_tokens(ms);
    ms_free_all_processes(ms);
	ms_set_error(ms->global_error, NO_ERROR, NULL);
    ft_printf("\n");
}

void launch_executer_run_pipeline(t_minishell *ms)
{
    ft_printf("\e[1;34mTest with command:\e[m %s\n", ms->full_command);
    ms_parser(ms);
	ms_lexer(ms);
    ms_executer(ms);
    display_tokens_types(ms);
    display_processes(ms);
    test_display_errors(ms);
    ms_free_all_tokens(ms);
    ms_free_all_processes(ms);
	ms_set_error(ms->global_error, NO_ERROR, NULL);
    ft_printf("\n");
}

void	test_processes_build(t_minishell *ms)
{
	printf("\e[1;34m===Testing processes===\e[m\n");
    ms->full_command = ft_strdup("env hello");
	launch_executer_build(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("cat cat | 'cat' $hello");
	launch_executer_build(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("env | echo | cat | ls");
	launch_executer_build(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("test ||| test");
	launch_executer_build(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("cat test | echo -o test | cd cd | echo | cat ");
	launch_executer_build(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("sad | das| | asd| Asd| sda |");
	launch_executer_build(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("'cat' | cat | \"cat\"");
	launch_executer_build(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("     'cat    ' |  cat   | \"     cat     \"");
	launch_executer_build(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("'$cat' | $cat | \"$cat\"");
	launch_executer_build(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("cd | cd");
	launch_executer_build(ms);
	free(ms->full_command);
}

void	test_processes_errors(t_minishell *ms)
{
	(void) ms;
	printf("\e[1;34m===Testing processes errors (BAD COMMANDS)===\e[m\n");
	// test_set_command(ms, "asd | echo hello | eee eee");
    ms->full_command = ft_strdup("asd | echo hello | eee eee");
	launch_executer_errors(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("echo hello");
	launch_executer_errors(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("echo test | asd hello | eee eee | echo hello | cat -e");
	launch_executer_errors(ms);
	free(ms->full_command);
	printf("\e[1;34m===Testing processes errors (SYNTAX PIPES)===\e[m\n");
}

static void	close_pipe(t_minishell *ms)
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
    ft_printf("\e[1;34mThe tokens are:\e[m \n");
    display_tokens_types(ms);
    ms_build_processes(ms);
    ft_printf("\e[1;34mThe processes are:\e[m \n");
	create_pipes(ms);
    display_processes(ms);
	close_pipe(ms);
    ms_free_all_tokens(ms);
    ms_free_all_processes(ms);
    ft_printf("\n");
}

void	test_processes_pipe(t_minishell *ms)
{
	printf("\e[1;34m===Testing processes===\e[m\n");
    ms->full_command = ft_strdup("env | wc");
	launch_executer_pipe(ms);
	free(ms->full_command);
    ms->full_command = ft_strdup("env | wc | wc -l");
	launch_executer_pipe(ms);
	free(ms->full_command);
}

void test_executer(t_minishell *ms, int debug)
{
	if (debug == TEST_EXECUTER_PROCESSES_BUILD)
		test_processes_build(ms);
	else if (debug == TEST_EXECUTER_PROCESSES_ERROR)
		test_processes_errors(ms);
	else if (debug == TEST_EXECUTER_PROCESSES_PIPE)
		test_processes_pipe(ms);
    else if (debug == TEST_EXECUTER  || debug == TEST_ALL)
    {
	    printf("===Testing EXECUTER===\n");
		test_processes_build(ms);
		test_processes_errors(ms);
	}
}
