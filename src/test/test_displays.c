#include "../../inc/minishell.h"

static void print_type(int t)
{
	if (t == NO_TYPE)
        ft_printf("NO_TYPE");
	else if (t == TYPE_ARG_STRING)
        ft_printf("ARG_STRING");
	else if (t == TYPE_ARG_OPTION)
        ft_printf("ARG_OPTION");
	else if (t == TYPE_PIPE)
        ft_printf("PIPE");
	else if (t == TYPE_S_QUOTE_STRING)
        ft_printf("SINGLE_QUOTE_STRING");
	else if (t == TYPE_D_QUOTE_STRING)
        ft_printf("DOUBLE_QUOTE_STRING");
	else if (t == TYPE_EXTERNAL_COMMAND)
        ft_printf("EXTERNAL_COMMAND");
	else if (t == TYPE_BUILTIN_COMMAND)
        ft_printf("BUILTIN_COMMAND");
	else if (t == TYPE_BAD_COMMAND)
        ft_printf("BAD_COMMAND");
	else if (t == TYPE_REDIRECT_LEFT)
        ft_printf("REDIRECT_LEFT");
	else if (t == TYPE_REDIRECT_DOUBLE_LEFT)
        ft_printf("REDIRECT_DOUBLE_LEFT");
	else if (t == TYPE_REDIRECT_RIGHT)
        ft_printf("REDIRECT_RIGHT");
	else if (t == TYPE_REDIRECT_DOUBLE_RIGHT)
        ft_printf("REDIRECT_DOUBLE_RIGHT");
	else if (t == TYPE_ARG_REDIRECT_FILE)
        ft_printf("TYPE_ARG_REDIRECT_FILE");
	else if (t == TYPE_ARG_DELIMITER)
        ft_printf("TYPE_ARG_DELIMITER");
}

// display all the tokens as a list
void test_display_tokens_types(t_minishell *ms)
{
    t_token *token;
    int i;

    i = 1;
    token = ms->first_token;
    ft_printf("\e[1;34mThe tokens are:\e[m \n");
    while (token)
    {
        ft_printf("%d:\n\tContent: \e[0;36m%s\e[m\n\tType:\e[0;36m", i, token->content);
        print_type(token->type);
    	ft_printf("\e[m\n");
        if (token->type == TYPE_EXTERNAL_COMMAND)
            ft_printf("\tExternal binary path: \e[0;32m%s\e[m\n", token->external_path);
        token = token->next;
        i++;
    }
}

void test_display_tokens(t_minishell *ms)
{
    t_token *token;
    int i;

    i = 1;
    token = ms->first_token;
    while (token)
    {
        ft_printf("%d:\n\tContent: \e[0;36m%s\e[m\n", i, token->content);
        token = token->next;
        i++;
    }
}

// display all the commands from processes rebuilt from token
void test_display_processes(t_minishell *ms)
{
	t_process *process;
	int i;
	int j;

	i = 1;
	process = ms->first_process;
    ft_printf("\e[1;34mThe processes are:\e[m \n");
	while (process)
	{
		ft_printf("%d:\n", i);
		ft_printf("\tProcess: \e[0;36m%p\e[m\n", process);
		ft_printf("\tProcess id: \e[0;36m%d\e[m\n", process->pid);
		j = 0;
		ft_printf("\tThe command line: ");
		while(process->cmd[j])
		{
			ft_printf(" %s", process->cmd[j]);
			j++;
		}
		ft_printf("\n\tExec path: %s", process->exec_path);
		ft_printf("\e[m\n");
		ft_printf("\tThe type line: \e[0;36m");
		j = 0;
		if (process->types_line)
		{
			while (process->types_line[j])
			{
				print_type(process->types_line[j]);
				ft_printf(" ");
				j++;
			}
		}
		ft_printf("\e[m\n");
		ft_printf("\tPipe In: \e[0;36m%d\e[m\n", process->pipe_in);
		ft_printf("\tPipe Out: \e[0;36m%d\e[m\n", process->pipe_out);
		ft_printf("\e[m\n");
		ft_printf("\tProcess next: \e[0;36m%p\e[m\n", process->next);
		ft_printf("\tProcess prev: \e[0;36m%p\e[m\n", process->prev);
		process = process->next;
		i++;
	}
}

void test_display_errors(t_minishell *ms)
{
	t_error	  *global_error;
	t_process *process;
	int i;

	global_error = ms->global_error;
    ft_printf("\e[1;34mThe errors are:\e[m \n");
    ft_printf("\e[1;34m\tGlobal:\e[m \n");
	ft_printf("\t\tHas global error: ");

	if (global_error->flag)
	{
		ft_printf("\e[0;31myes\e[m\n");
		ft_printf("\t\tError message: \e[0;31m%s\e[m\n", global_error->msg);

	}
	else
		ft_printf("\e[0;32mno\e[m\n");

    ft_printf("\e[1;34m\tInternal:\e[m \n");
	process = ms->first_process;
	i = 1;

	while (process)
	{
		ft_printf("\t\t%d:", i);
		if (process->internal_error->flag)
		{
			ft_printf(" Internal error: \e[0;31m%s\e[m\n", process->internal_error->msg);
		}
		else
			ft_printf(" \e[0;32mNo internal error.\e[m\n");
		process = process->next;
		i++;
	}
}

void	test_display_local_env(t_minishell *ms)
{
	t_variable	*env;

	env = ms->first_var;
	while (env)
	{
		ft_printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
}

void	test_reset(t_minishell *ms)
{
	ms_free_last_command(ms);
	ms_set_error(ms->global_error, NO_ERROR, NULL);
    ft_printf("\n");
}

void test_display_redirections(t_minishell *ms)
{
	t_process 		*process;
	t_redirection	*redirection;
	int i;

	i = 1;
	process = ms->first_process;
	while (process)
	{
		ft_printf("Process %d:\n", i);
		if (process->has_redirection)
		{
			redirection = process->first_redirection;
			while (redirection)
			{
				ft_printf("\tRedirection type: ");
				print_type(redirection->type);
				ft_printf("\n\tRedirection filepath: %s\n", redirection->filepath);
				redirection = redirection->next;
			}
		}
		else
			ft_printf("has no redirection!\n");
		process = process->next;
		i++;
	}
}
