/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_analyze_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:07:36 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/09 08:36:30 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// Give type for each pipe
void ms_analyze_pipes(t_minishell *ms)
{
    t_token *token;

    token = ms->first_token;
    while(token)
    {
        if (!ft_strncmp("|", token->content, ft_strlen(token->content)))
        {
            token->type = TYPE_PIPE;
            ms_analyze_command(ms, token->next);
        }
        token = token->next;
    }
}