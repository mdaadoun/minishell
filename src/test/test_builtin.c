#include "../../inc/minishell.h"

static void	display_local_env(t_minishell *ms)
{
	t_variable	*env;

	env = ms->first_var;
	while (env)
	{
		ft_printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
}

static void	launch_unset(t_minishell *ms, char *export, char *unset)
{
	ms_export(ms, export);
	ft_printf("==============================================================\n");
	ft_printf("Local ENV before UNSET\n");
	display_local_env(ms);
	ft_printf("==============================================================\n");
	ft_printf("Local ENV after UNSET \"%s\"\n", unset);
	ms_unset(ms, unset);
	display_local_env(ms);
	ft_printf("==============================================================\n");
}

static void	test_unset(t_minishell *ms)
{
	launch_unset(ms, "export a=1 b=2 c=3 d=4", "unset b c");
	launch_unset(ms, "export best=architect", "unset seeker");
}

static void	launch_export(t_minishell *ms, char *export)
{
	ft_printf("==============================================================\n");
	ft_printf("Local ENV after EXPORT \"%s\"\n", export);
	ms_export(ms, export);
	display_local_env(ms);
	ft_printf("==============================================================\n");
}

static void	test_export(t_minishell *ms)
{
	launch_export(ms, "export abs=echo ep=$abs");
	launch_export(ms, "export seeker");
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
