/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:27:14 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/06 09:31:11 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_uint8 ms_pwd(void)
{
    char cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
    {
		ft_printf("%s\n", cwd);
		return (SUCCESS);
	}
	else
		return (ERROR_PWD);
}
