#include "../../inc/minishell.h"


void print_type(int t)
{
	if (t == NO_TYPE)
        ft_printf("NO_TYPE");
	else if (t == TYPE_ARG_STRING)
        ft_printf("ARG_STRING");
	else if (t == TYPE_ARG_OPTION)
        ft_printf("ARG_OPTION");
	else if (t == TYPE_PIPE)
        ft_printf("PIPE");
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
}

// display all the tokens as a list
void display_tokens_types(t_minishell *ms)
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

void display_tokens(t_minishell *ms)
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
void display_processes(t_minishell *ms)
{
	t_process *process;
	int i;
	int j;

	i = 1;
	process = ms->first_process;
    ft_printf("\e[1;34mThe processes are:\e[m \n");
	ft_printf("Has pipes: ");

	if (ms->has_pipe)
		ft_printf("\e[0;32myes\e[m\n");
	else
		ft_printf("\e[0;31mno\e[m\n");

	ft_printf("Nb of processes: \e[0;33m%d\e[m\n", ms->nb_processes);
	while (process)
	{
		ft_printf("%d:\n", i);
		ft_printf("\tNumber of tokens: \e[0;36m%d\e[m\n", process->nb_tokens);
		ft_printf("\tProcess id: \e[0;36m%d\e[m\n", process->pid);
		ft_printf("\tThe command line: \e[0;36m%s\e[m\n", process->command_line);
		ft_printf("\tPipe In: \e[0;36m%d\e[m\n", process->pipe_in);
		ft_printf("\tPipe Out: \e[0;36m%d\e[m\n", process->pipe_out);
		ft_printf("\tThe type line: \e[0;36m");
		j = 0;
		while (j < process->nb_tokens)
		{
			print_type(process->types_line[j]);
			ft_printf(" ");
			j++;
		}
		ft_printf("\e[m\n");
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
