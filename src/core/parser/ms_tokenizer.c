/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:55:29 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/12 07:19:21 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
 * The new token is added at the end of the token structure.
 */
static void	push_after_last_token(t_token *first, t_token *last)
{
	t_token	*tmp;

	tmp = first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = last;
	last->prev = tmp;
}

/*
 * Return a pointer to the allocated memory for a new t_token element.
 */
t_token	*ms_create_new_token(t_minishell *ms)
{
	t_token	*token;

	token = (t_token *) ft_calloc(sizeof(t_token), 1);
	if (!token)
	{
		ms_set_error(ms->global_error, ERROR_MALLOC, MSG_ERROR_MALLOC);
		exit(ms_free_before_exit(ms));
	}
	token->type = NO_TYPE;
	token->content = NULL;
	token->next = NULL;
	return (token);
}

/*
 * Check if it the first token
 */
void	ms_add_token(t_minishell *ms, char *content, t_token_type type)
{
	t_token	*token;

	token = ms_create_new_token(ms);
	token->content = content;
	token->type = type;
	if (!ms->first_token)
		ms->first_token = token;
	else
		push_after_last_token(ms->first_token, token);
}

// create a function to add a token next to a given token
void	ms_append_token(t_token *before_token, t_token *add_token)
{
	add_token->next = before_token->next;
	add_token->prev = before_token;
	before_token->next = add_token;
}

// delete token, connect prev to next and return next token
// prev_token <-> token <-> next_token
// prev_token <-> next_token
t_token	*ms_delete_token(t_token *token)
{
	t_token	*prev_token;
	t_token	*next_token;

	prev_token = token->prev;
	next_token = token->next;
	if (prev_token)
		prev_token->next = next_token;
	else if (next_token)
		next_token->prev = NULL;
	if (next_token)
		next_token->prev = prev_token;
	else if (prev_token)
		prev_token->next = NULL;
	free(token->content);
	free(token);
	if (next_token)
		return (next_token);
	else
		return (NULL);
}
