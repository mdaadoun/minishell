/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_analyze_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:07:36 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/09 08:57:25 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// Give type for each token with a redirection
void ms_analyze_redirections(t_minishell *ms)
{
    t_token *token;

    token = ms->first_token;
    while(token)
    {
        if (token->type == NO_TYPE)
        {
            if (!ft_strncmp("<", token->content, ft_strlen(token->content)))
                token->type = TYPE_REDIRECT_LEFT;
            else if (!ft_strncmp(">", token->content, ft_strlen(token->content)))
                token->type = TYPE_REDIRECT_RIGHT;
            else if (!ft_strncmp("<<", token->content, ft_strlen(token->content)))
                token->type = TYPE_REDIRECT_DOUBLE_LEFT;
            else if (!ft_strncmp(">>", token->content, ft_strlen(token->content)))
                token->type = TYPE_REDIRECT_DOUBLE_RIGHT;
        }
        token = token->next;
    }
}
