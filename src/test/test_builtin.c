#include "../../inc/minishell.h"

void test_builtin(int argc, char **argv, char **envp)
{
    int test;

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
        ft_printf("builtin test error\n");
    (void) argc;
    (void) argv;
    (void) envp;
}
