#include "../../inc/minishell.h"

void test_executer_redirections(t_minishell *ms, int debug)
{
	if (debug == TEST_EXECUTER_REDIRECTIONS)
		test_redirections(ms, debug);
}
