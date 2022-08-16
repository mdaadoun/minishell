#include "../../inc/minishell.h"


void test_run_command(t_minishell *ms, char *str, int debug)
{
    ms->full_command = ft_strdup(str);
    ft_printf("\n================================\n\e[1;34mTest command:\e[m %s\n================================\n", ms->full_command);
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
    ft_printf("\t\e[1;33m%d:\e[m all\n", TEST_ALL);
    ft_printf("\t\e[1;33m%d:\e[m parser\n", TEST_PARSER);
    ft_printf("\t\e[1;33m  %d:\e[m quotes\n", TEST_PARSER_QUOTES);
    ft_printf("\t\e[1;33m  %d:\e[m pipes\n", TEST_PARSER_PIPES);
    ft_printf("\t\e[1;33m  %d:\e[m variables\n", TEST_PARSER_ENV);
    ft_printf("\t\e[1;33m  %d:\e[m arguments\n", TEST_PARSER_ARGUMENTS);
    ft_printf("\t\e[1;33m  %d:\e[m redirections\n", TEST_PARSER_REDIRECTIONS);
    ft_printf("\t\e[1;33m%d:\e[m lexer\n", TEST_LEXER);
    ft_printf("\t\e[1;33m  %d:\e[m builtins command\n", TEST_LEXER_BUILTINS);
    ft_printf("\t\e[1;33m  %d:\e[m external command\n", TEST_LEXER_EXTERNALS);
    ft_printf("\t\e[1;33m  %d:\e[m pipes\n", TEST_LEXER_PIPES);
    ft_printf("\t\e[1;33m  %d:\e[m redirections\n", TEST_LEXER_REDIRECTIONS);
    ft_printf("\t\e[1;33m  %d:\e[m arguments\n", TEST_LEXER_ARGUMENTS);
    ft_printf("\t\e[1;33m%d:\e[m builtin command\n", TEST_BUILTIN);
    ft_printf("\t\e[1;33m  %d:\e[m pwd\n", TEST_BUILTIN_PWD);
    ft_printf("\t\e[1;33m  %d:\e[m env\n", TEST_BUILTIN_ENV);
    ft_printf("\t\e[1;33m  %d:\e[m export\n", TEST_BUILTIN_EXPORT);
    ft_printf("\t\e[1;33m  %d:\e[m unset\n", TEST_BUILTIN_UNSET);
    ft_printf("\t\e[1;33m%d:\e[m executer\n", TEST_EXECUTER);
    ft_printf("\t\e[1;33m  %d:\e[m test building processes\n", TEST_EXECUTER_PROCESSES_BUILD);
    ft_printf("\t\e[1;33m  %d:\e[m test building errors\n", TEST_EXECUTER_PROCESSES_ERROR);
    ft_printf("\t\e[1;33m  %d:\e[m test building pipes\n", TEST_EXECUTER_PROCESSES_PIPE);
    ft_printf("\t\e[1;33m  %d:\e[m test process execv\n", TEST_EXECUTER_PROCESSES_EXECV);
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
