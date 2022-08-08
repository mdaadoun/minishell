/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 09:04:20 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/08 16:58:02 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
 * analyze each token following this order and set types:
 *		1. Check if first token is valid command
 *      2. Tag all Pipes and check if next token is a valid token
 *      	* Check token is external or builtin programs
 *      x. Redirections ?
 *      x. If valid syntax, checking errors and ignore if not
 * 		last. check last NO_TYPE if string arg or option
*/
void ms_lexer(t_minishell *ms)
{
	ms_analyze_command(ms, ms->first_token);
	ms_analyze_pipes(ms);
}
