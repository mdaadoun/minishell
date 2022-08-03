/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:43:46 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/03 13:58:53 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// check if the command is external or builtin, 
//      * tag correct type, return true
//      * error, return false
bool ms_is_valid_command(t_minishell *ms)
{
    char *command;

    command = ms->first_token->content;
    ft_printf("is valid command ? %s\n", command);
    return (false);
}
