/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:12:25 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/17 09:40:07 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"


static void open_heredoc(t_token *token, t_process *process)
{
	(void) token;	
	(void) process;	
}

/*
 *	First check if the current token is a redirection operator.
 *	Then check differents operators:
 *		1. >>
 *		2. <<
			if there is a delimiter open heredoc, else it is a syntax error 
 *		3. <
 *		4. >
*/
void ms_build_redirections(t_minishell *ms, t_token *token,	t_process *process)
{
	t_err_key 	err_key;
	char 		*err_msg;
	
	err_key = ERROR_SYNTAX;
	err_msg = MSG_ERROR_SYNTAX_REDIRECT;
	if (token->type == TYPE_REDIRECT_DOUBLE_RIGHT || 
		token->type == TYPE_REDIRECT_DOUBLE_LEFT || 
		token->type == TYPE_REDIRECT_LEFT || 
		token->type == TYPE_REDIRECT_RIGHT)
			process->has_redirection = true;

	if (token->type == TYPE_REDIRECT_DOUBLE_RIGHT) 
		ft_printf("redirection double right.");

	else if	(token->type == TYPE_REDIRECT_DOUBLE_LEFT)
		if (token->next->type == TYPE_ARG_STRING)
			open_heredoc(token, process);
		else
			ms_set_error(process->internal_error, err_key, err_msg);

	else if	(token->type == TYPE_REDIRECT_LEFT)
		ft_printf("redirection left");
	else if	(token->type == TYPE_REDIRECT_RIGHT)
		ft_printf("redirectoin right");
	(void) ms;
}