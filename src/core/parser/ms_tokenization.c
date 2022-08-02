/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:55:29 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/02 17:27:11 by mdaadoun         ###   ########.fr       */
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
}

/*
 * Return a pointer to the allocated memory for a new t_token element.
*/
static t_token *create_new_token(t_minishell *ms)
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
void ms_add_token(t_minishell *ms, char* content)
{
    t_token *token;

    token = create_new_token(ms);
    token->content = content;
    if (!ms->first_token)
        ms->first_token = token;
    else
        push_after_last_token(ms->first_token, token);
}