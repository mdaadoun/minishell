#include "../../inc/minishell.h"


void test_run_command(t_minishell *ms, char *str, int debug)
{
    ms->full_command = ft_strdup(str);
    ft_printf("\n\e[1;34mTest command:\e[m %s\n", ms->full_command);
    test_launcher(ms, debug);
}

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
    ft_printf("\nuse the command:\n\t\e[1;33m./minishell <option> <number_test> <command>\e[m\n");
    ft_printf("\n\e[0;32mThe <option> list:\e[m\n");
    ft_printf("\tif no option, unit-test assert only.\n");
    ft_printf("\t\e[1;33mv:\e[m verbose, for debug.\n");
    ft_printf("\t\e[1;33mc:\e[m a <command> is given as parameter.\n");
    ft_printf("\n\e[0;32mThe <number_test> list:\e[m\n");
    ft_printf("\t\e[1;33m0:\e[m all\n");
    ft_printf("\t\e[1;33m1:\e[m parser\n");
    ft_printf("\t\e[1;33m  11:\e[m quotes\n");
    ft_printf("\t\e[1;33m  12:\e[m pipes\n");
    ft_printf("\t\e[1;33m  13:\e[m variables\n");
    ft_printf("\t\e[1;33m2:\e[m lexer\n");
    ft_printf("\t\e[1;33m  21:\e[m builtins command\n");
    ft_printf("\t\e[1;33m  22:\e[m external command\n");
    ft_printf("\t\e[1;33m  23:\e[m pipes\n");
    ft_printf("\t\e[1;33m  24:\e[m redirections\n");
    ft_printf("\t\e[1;33m  25:\e[m arguments\n");
    ft_printf("\t\e[1;33m3:\e[m builtin command\n");
    ft_printf("\t\e[1;33m  31:\e[m pwd\n");
    ft_printf("\t\e[1;33m  32:\e[m env\n");
    ft_printf("\t\e[1;33m  33:\e[m export\n");
    ft_printf("\t\e[1;33m  34:\e[m unset\n");
    ft_printf("\t\e[1;33m4:\e[m executer\n");
    ft_printf("\t\e[1;33m  41:\e[m test building processes\n");
    ft_printf("\t\e[1;33m  42:\e[m test building errors\n");
    ft_printf("\t\e[1;33m  43:\e[m test building pipes\n");
    ft_printf("\t\e[1;33m  44:\e[m test process execv\n");
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

void test_start(int argc, char **argv, char **envp)
{
	t_minishell *ms;
	t_error		error;
    int     debug;

	if (argc >= 2)
	{
		ms_initialize_minishell(&ms, &error, envp);
	    ms_initialize_signals();
        if (!ft_strncmp(argv[1], "v", 1))
        {
            ft_printf("verbose mode");
        }
        else if (!ft_strncmp(argv[1], "c", 1))
        {
            ft_printf("test a specific command");
        }
        else
        {
            debug = ft_atoi(argv[1]);
            set_and_run_tests(ms, debug);
            free_test(ms);
        }
	}
	else
		display_help();
    exit(0);
}
