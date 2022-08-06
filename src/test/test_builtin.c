#include "../../inc/minishell.h"

void test_builtin(t_minishell *ms, int debug)
{
	if (debug == TEST_BUILTIN)
	{
		ms_pwd();
	}
	if (debug == TEST_BUILTIN_PWD)
	{
		ms_pwd();
	}
/*    int test;

    test = 0;
    ft_printf("Testing the builtin functions.\n");
    test = ms_echo(argv, 'n');
    test = ms_cd(argv);
    test = ms_pwd(argv);
    test = ms_export(argv);
    test = ms_unset(argv);
    test =  ms_env(envp);
    test = ms_exit();
    if (test)
        ft_printf("builtin test error\n");*/
}
