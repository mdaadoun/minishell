/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:27:14 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/08 17:15:30 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// print name of current/working directory
t_uint8 ms_pwd(void)
{
    char cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
    {
		ft_printf("%s\n", cwd);
		return (0);
	}
	else
		return (1);
}
