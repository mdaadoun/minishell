#include "../../inc/minishell.h"


void test_run_command(t_minishell *ms, char *str, int debug)
{
    ms->full_command = ft_strdup(str);
    ft_printf("\n================================\n\e[1;34mTest command:\e[m %s\n================================\n", ms->full_command);
    test_launcher(ms, debug);
	test_reset(ms);
}

static void set_and_run_tests(t_minishell *ms, int debug)
{
    test_parser(ms, debug);
    test_analyzer(ms, debug);
	test_builtin(ms, debug);
	test_executer_build(ms, debug);
	test_executer_errors(ms, debug);
    test_executer_redirections(ms, debug);
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
    ft_printf("\t\e[1;33m  %d:\e[m env / variables\n", TEST_PARSER_ENV);
    ft_printf("\t\e[1;33m  %d:\e[m arguments\n", TEST_PARSER_ARGUMENTS);
    ft_printf("\t\e[1;33m  %d:\e[m redirections\n", TEST_PARSER_REDIRECTIONS);
    ft_printf("\t\e[1;33m  %d:\e[m builtins programs\n", TEST_PARSER_BUILTINS);
    ft_printf("\t\e[1;33m  %d:\e[m externals programs\n", TEST_PARSER_EXTERNALS);
    ft_printf("\t\e[1;33m%d:\e[m analyzer\n", TEST_ANALYZER);
    ft_printf("\t\e[1;33m  %d:\e[m quotes\n", TEST_ANALYZER_QUOTES);
    ft_printf("\t\e[1;33m  %d:\e[m pipes\n", TEST_ANALYZER_PIPES);
    ft_printf("\t\e[1;33m  %d:\e[m env / variables\n", TEST_ANALYZER_ENV);
    ft_printf("\t\e[1;33m  %d:\e[m arguments\n", TEST_ANALYZER_ARGUMENTS);
    ft_printf("\t\e[1;33m  %d:\e[m redirections\n", TEST_ANALYZER_REDIRECTIONS);
    ft_printf("\t\e[1;33m  %d:\e[m builtins command\n", TEST_ANALYZER_BUILTINS);
    ft_printf("\t\e[1;33m  %d:\e[m external command\n", TEST_ANALYZER_EXTERNALS);
    ft_printf("\t\e[1;33m%d:\e[m executer build processes\n", TEST_EXECUTER_BUILD);
    ft_printf("\t\e[1;33m  %d:\e[m quotes\n", TEST_EXECUTER_BUILD_QUOTES);
    ft_printf("\t\e[1;33m  %d:\e[m pipes\n", TEST_EXECUTER_BUILD_PIPES);
    ft_printf("\t\e[1;33m  %d:\e[m env / variables\n", TEST_EXECUTER_BUILD_ENV);
    ft_printf("\t\e[1;33m  %d:\e[m arguments\n", TEST_EXECUTER_BUILD_ARGUMENTS);
    ft_printf("\t\e[1;33m  %d:\e[m redirections\n", TEST_EXECUTER_BUILD_REDIRECTIONS);
    ft_printf("\t\e[1;33m  %d:\e[m builtins command\n", TEST_EXECUTER_BUILD_BUILTINS);
    ft_printf("\t\e[1;33m  %d:\e[m external command\n", TEST_EXECUTER_BUILD_EXTERNALS);
    ft_printf("\t\e[1;33m%d:\e[m executer errors\n", TEST_EXECUTER_ERRORS);
    ft_printf("\t\e[1;33m  %d:\e[m quotes\n", TEST_EXECUTER_ERRORS_QUOTES);
    ft_printf("\t\e[1;33m  %d:\e[m pipes\n", TEST_EXECUTER_ERRORS_PIPES);
    ft_printf("\t\e[1;33m  %d:\e[m env / variables\n", TEST_EXECUTER_ERRORS_ENV);
    ft_printf("\t\e[1;33m  %d:\e[m arguments\n", TEST_EXECUTER_ERRORS_ARGUMENTS);
    ft_printf("\t\e[1;33m  %d:\e[m redirections\n", TEST_EXECUTER_ERRORS_REDIRECTIONS);
    ft_printf("\t\e[1;33m  %d:\e[m builtins command\n", TEST_EXECUTER_ERRORS_BUILTINS);
    ft_printf("\t\e[1;33m  %d:\e[m external command\n", TEST_EXECUTER_ERRORS_EXTERNALS);
    ft_printf("\t\e[1;33m%d:\e[m executor redirections\n", TEST_EXECUTER_REDIRECTIONS);
    ft_printf("\t\e[1;33m%d:\e[m builtin command\n", TEST_BUILTIN);
    ft_printf("\t\e[1;33m  %d:\e[m pwd\n", TEST_BUILTIN_PWD);
    ft_printf("\t\e[1;33m  %d:\e[m env\n", TEST_BUILTIN_ENV);
    ft_printf("\t\e[1;33m  %d:\e[m export\n", TEST_BUILTIN_EXPORT);
    ft_printf("\t\e[1;33m  %d:\e[m unset\n", TEST_BUILTIN_UNSET);
}

void test_start(int argc, char **argv, char **envp)
{
	t_minishell *ms;
	t_error     error;

	if (argc >= 2)
	{
		ms_initialize_minishell(&ms, &error, envp);
	    ms_initialize_signals();
        if (!ft_strncmp(argv[1], "v", 1))
            ft_printf("TODO: verbose mode not by default.");
        else if (!ft_strncmp(argv[1], "c", 1))
            ft_printf("TODO: test a specific command.");
        else
            set_and_run_tests(ms, ft_atoi(argv[1]));
        exit(ms_free_before_exit(ms));
	}
	else
		display_help();
    exit(0);
}
