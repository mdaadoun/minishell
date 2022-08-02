#include "../../inc/minishell.h"
#include <assert.h>

static void set_and_run_tests(t_minishell *ms)
{
    test_parser(ms);
    // test_builtin(ms);
}

void run_test(int argc, char **argv, char **envp)
{
    char *line;
	t_minishell *ms;

	ms_initialize_minishell(&ms);
    if (argc == 2)
        ms->line = argv[1];
    set_and_run_tests(ms);
    free(ms);
    exit(ms_free_before_exit(NULL, SUCCESS));
}
