/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:46:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/02 10:06:03 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
 * Dynamic structure of variables
*/
t_uint8 ms_export(char **args)
{
    (void) args;
    ft_printf("export\n");
    return (SUCCESS);
}