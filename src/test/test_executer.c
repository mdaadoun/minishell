#include "../../inc/minishell.h"

void launch_executer_build(t_minishell *ms)
{

    ft_printf("\e[1;34mTest with command:\e[m %s\n", ms->full_command);
    ms_parser(ms);
	ms_lexer(ms);
    ft_printf("\e[1;34mThe tokens are:\e[m \n");
    display_tokens(ms);
    ms_free_all_tokens(ms);
    ft_printf("\e[1;34mThe commands are:\e[m \n");
    ft_printf("\n");
}

void	test_processes_build(t_minishell *ms)
{
	printf("===Testing processes===\n");
    ms->full_command = ft_strdup("env hello");
	launch_executer_build(ms);
	free(ms->full_command);
}

void test_executer(t_minishell *ms, int debug)
{
	if (debug == TEST_EXECUTER_PROCESSES_BUILD)
		test_processes_build(ms);
    else if (debug == TEST_EXECUTER)
    {
	    printf("===Testing EXECUTER===\n");
		test_processes_build(ms);
	}
}
