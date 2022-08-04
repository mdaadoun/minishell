/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 09:04:20 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/04 12:20:25 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
 * Analyse each token following this order and set types:
 *		1. Check if first token is valid command
 *      2. Tag all Pipes and check if next token is a valid token
 *      	* Check token is external or builtin programs
 *      x. Redirections ?
 *      x. If valid syntax, checking errors and ignore if not
 * 		last. check last NO_TYPE if string arg or option
*/
void ms_lexer(t_minishell *ms)
{
	ms_analyze_pipes(ms);
	// Check first command and each after each pipes
	if(!ms_is_valid_command(ms, ms->first_token))
		exit(ms_free_before_exit(ms, ERROR_COMMAND));
}
