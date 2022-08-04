#include "../../inc/minishell.h"

static void set_and_run_tests(t_minishell *ms, int debug)
{
    test_parser(ms, debug);
    test_lexer(ms, debug);
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
    ft_printf("  21: builtins\n");
    ft_printf("  22: external\n");
    ft_printf("  23: pipes\n");
}

void run_test(int argc, char **argv, char **envp)
{
    char *line;
	t_minishell *ms;
    int     debug;

    // if (argv )
	ms_initialize_minishell(&ms);
    if (argc == 2)
    {
        if (argv[1][0] == 'h')
        {
            display_help();
            exit(ms_free_before_exit(NULL, SUCCESS));
        }
        else
            debug = ft_atoi(argv[1]);
    }
    set_and_run_tests(ms, debug);
    free(ms);
    exit(ms_free_before_exit(NULL, SUCCESS));
}
