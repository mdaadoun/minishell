#include "../../inc/minishell.h"


// display all the tokens
void display_tokens(t_minishell *ms)
{
    t_token *token;

    token = ms->first_token;

    while (token)
    {
        ft_printf("Content: %s		Type: %d\n", token->content, token->type);
        token = token->next;
    }
}

// display all the commands from processes
void display_commands(t_minishell *ms)
{
	(void) ms;
}