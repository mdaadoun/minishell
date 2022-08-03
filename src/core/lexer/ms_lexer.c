/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 09:04:20 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/03 13:53:41 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
 * Analyse each token following this order and set types:
 *      1. If the token is valid command (external or builtin programs)
 *      x. Pipes ?
 *      x. Redirections ?
 *      x. If valid syntax, checking errors and ignore if not
*/
void ms_lexer(t_minishell *ms)
{
	if(!ms_is_valid_command(ms))
		exit(ms_free_before_exit(ms, ERROR_COMMAND));
}
