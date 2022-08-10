#include "../../inc/minishell.h"

static void	test_unset(t_minishell *ms)
{
	ms_export(ms, "export a=1 b=2 c=3 d=4");
	ms_unset(ms, "unset b c");
	ms_env(ms);
}

void test_builtin(t_minishell *ms, int debug)
{
	if (debug == TEST_BUILTIN)
		ms_pwd();
	if (debug == TEST_BUILTIN_PWD)
		ms_pwd();
	if (debug == TEST_BUILTIN_ENV)
		ms_env(ms);
	if (debug == TEST_BUILTIN_EXPORT || debug == TEST_ALL)
	{
		ms_export(ms, "export abs=echo e=$abs");
		ms_env(ms);
	}
	if (debug == TEST_BUILTIN_UNSET)
		test_unset(ms);
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
