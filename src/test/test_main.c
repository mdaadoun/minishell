#include "../../inc/minishell.h"

static void set_and_run_tests(t_minishell *ms, int debug)
{
    test_parser(ms, debug);
    test_lexer(ms, debug);
	test_builtin(ms, debug);
	test_executer(ms, debug);
}

void display_help()
{
	ft_printf("\e[1;44m=============================\e[m\n");
    ft_printf("\e[1;47;30mHELP for the MINISHELL TESTER\e[m\n");
	ft_printf("\e[1;41m=============================\e[m\n");
    ft_printf("\nuse the command:\n\t./minishell <number_test>\n\n");
    ft_printf("The <number_test> list:\n");
    ft_printf("0: all\n");
    ft_printf("1: parser\n");
    ft_printf("  11: quotes\n");
    ft_printf("  12: pipes\n");
    ft_printf("  13: variables\n");
    ft_printf("2: lexer\n");
    ft_printf("  21: builtins command\n");
    ft_printf("  22: external command\n");
    ft_printf("  23: pipes\n");
    ft_printf("  24: redirections\n");
    ft_printf("  25: arguments\n");
    ft_printf("3: builtin command\n");
    ft_printf("  31: pwd\n");
    ft_printf("  32: env\n");
    ft_printf("  33: export\n");
    ft_printf("4: executer\n");
    ft_printf("  41: test building processes\n");
    ft_printf("  42: test building errors\n");
}

void	free_test(t_minishell *ms)
{
	size_t	ind;

	ind = 0;
	while (ms->bin_paths[ind])
	{
		free(ms->bin_paths[ind]);
		ind++;
	}
	free(ms->bin_paths);
	free(ms->cwd_path);
	free(ms);
}

void run_test(int argc, char **argv, char **envp)
{
    // char *line;
	t_minishell *ms;
    int     debug;

	if (argc == 2)
	{
		ms_initialize_minishell(&ms);
		ms->envp = envp;
		debug = ft_atoi(argv[1]);
    	set_and_run_tests(ms, debug);
   		free_test(ms);
	}
	else
		display_help();
    exit(0);
}
