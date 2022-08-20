#include "../../inc/minishell.h"

static void	arg_free(char **arg)
{
	int	ind;

	ind = 0;
	while (arg[ind])
	{
		free(arg[ind]);
		ind++;
	}
	free(arg);
}

static void	launch_unset(t_minishell *ms, char *export, char *unset)
{
	char	**arg;

	arg = ft_split(export, ' ');
	ms_export(ms, arg);
	arg_free(arg);
	ft_printf("==============================================================\n");
	ft_printf("Local ENV before UNSET\n");
	test_display_local_env(ms);
	ft_printf("==============================================================\n");
	ft_printf("Local ENV after UNSET \"%s\"\n", unset);
	arg = ft_split(unset, ' ');
	ms_unset(ms, arg);
	arg_free(arg);
	test_display_local_env(ms);
	ft_printf("==============================================================\n");
}

static void	test_unset(t_minishell *ms)
{
	launch_unset(ms, "export a=1 b=2 c=3 d=4", "unset b c");
	launch_unset(ms, "export best=architect", "unset seeker");
}

static void	launch_export(t_minishell *ms, char *export)
{
	char	**arg;

	ft_printf("==============================================================\n");
	ft_printf("Local ENV after EXPORT \"%s\"\n", export);
	arg = ft_split(export, ' ');
	ms_export(ms, arg);
	arg_free(arg);
	test_display_local_env(ms);
	ft_printf("==============================================================\n");
}

static void	test_export(t_minishell *ms)
{
	launch_export(ms, "export abs=echo ep=$abs");
	launch_export(ms, "export seeker");
}

// ECHO TEST
// static void	test_echo(t_minishell *ms)
// {
// 'echo test tout'
// 'echo test      tout'
// 'echo -n test tout'
// 'echo -n -n -n test tout'
// }

// CD TESTS
// static void	test_cd(t_minishell *ms)
// {
// 'cd .. ; pwd'
// 'cd /Users ; pwd'
// 'cd ; pwd'
// 'mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd'
// }

// CD EXIT
// static void	test_exit(t_minishell *ms)
// {
// "exit 42"
// "exit 42 53 68"
// "exit 259"
// "exit 9223372036854775807"
// "exit -9223372036854775808"
// "exit 9223372036854775808"
// "exit -9223372036854775810"
// "exit -4"
// "exit wrong"
// "exit wrong_command"
// "gdagadgag"
// "ls -Z"
// "cd gdhahahad"
// "ls -la | wtf"
// }


void test_builtin(t_minishell *ms, int debug)
{
	if (debug == TEST_BUILTIN)
		ms_pwd();
	if (debug == TEST_BUILTIN_PWD)
		ms_pwd();
	if (debug == TEST_BUILTIN_ENV)
		ms_env(ms);
	if (debug == TEST_BUILTIN_EXPORT || debug == TEST_ALL)
		test_export(ms);
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
