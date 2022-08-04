/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:55:29 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/04 08:20:09 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../inc/minishell.h"

/*
 * The new token is added at the end of the token structure.
*/
static  void push_after_last_token(t_token *first, t_token *last)
{
    t_token *tmp;

    tmp = first;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = last;
	last->prev = tmp;
}

/*
 * Return a pointer to the allocated memory for a new t_token element.
*/
t_token *ms_create_new_token(t_minishell *ms)
{
    t_token *token;

    token = (t_token *) ft_calloc(sizeof(t_token), 1);
    if (!token)
        exit(ms_free_before_exit(ms, ERROR_ALLOC));
    token->type = NO_TYPE;
    token->content = NULL;
    token->next = NULL;
    return (token);
}

/*
 * Free all the tokens of the ms structure.
*/
void ms_free_all_tokens(t_minishell *ms)
{
    t_token *token;
    t_token *swp;

    token = ms->first_token;
    while (token)
    {
        swp = token->next;
        free(token->content);
        free(token);
        token = swp;
    }
    ms->first_token = NULL;
}

/*
 * Check if it the first token
*/
void	ms_add_token(t_minishell *ms, char* content, t_token_type type)
{
    t_token *token;

    token = ms_create_new_token(ms);
    token->content = content;
    token->type = type;
    if (!ms->first_token)
        ms->first_token = token;
    else
        push_after_last_token(ms->first_token, token);
}

// create a function to add a token next to a given token
void ms_append_token(t_token *before_token, t_token *add_token)
{
	add_token->next = before_token->next;
	add_token->prev = before_token;
	before_token->next = add_token;
}
