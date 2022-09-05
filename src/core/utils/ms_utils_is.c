/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:40:46 by dlaidet           #+#    #+#             */
/*   Updated: 2022/09/05 13:42:37 by dlaidet          ###   ########.fr       */
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
