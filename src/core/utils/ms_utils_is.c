/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_is.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:40:46 by dlaidet           #+#    #+#             */
/*   Updated: 2022/09/05 15:01:34 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

bool	is_builtin_fork(t_builtins built)
{
	if (built == BIN_CD)
		return (false);
	if (built == BIN_EXPORT)
		return (false);
	if (built == BIN_UNSET)
		return (false);
	if (built == BIN_EXIT)
		return (false);
	return (true);
}

int	is_redirect(t_token *tok)
{
	if (tok->type == TYPE_REDIRECT_LEFT)
		return (4);
	else if (tok->type == TYPE_REDIRECT_RIGHT)
		return (3);
	else if (tok->type == TYPE_REDIRECT_DOUBLE_RIGHT)
		return (2);
	else if (tok->type == TYPE_REDIRECT_DOUBLE_LEFT)
		return (1);
	return (0);
}
