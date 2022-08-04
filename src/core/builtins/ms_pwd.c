/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:27:14 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/01 11:42:16 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_uint8 ms_pwd(char **args)
{
    (void) args;
    ft_printf("pwd\n");
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
    return (SUCCESS);
}