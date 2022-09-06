/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:27:14 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/06 17:50:12 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// print name of current/working directory
void	ms_pwd(t_minishell *ms, char **arg)
{
	char		cwd[PATH_MAX];
	t_err_key	err_key;
	char		*err_msg;

	err_key = ERROR_BUILTIN_OPTION;
	err_msg = MSG_ERROR_BUILTIN_OPTION;
	if (arg[1] && arg[1][0] == '-' && arg[1][1])
	{
		ms_set_error(ms->global_error, err_key, err_msg);
		g_sig.exit_status = 2;
	}
	else
	{
		if (getcwd(cwd, PATH_MAX))
			ft_printf("%s\n", cwd);
		g_sig.exit_status = 0;
	}
}
