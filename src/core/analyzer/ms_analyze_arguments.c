/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_analyze_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:07:36 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/14 09:15:35 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
 * Check if token left with NO_TYPE are option (with -) or simply text
 */
void	ms_analyze_arguments(t_minishell *ms)
{
	t_token	*token;

	token = ms->first_token;
	while (token)
	{
		if (token->type == NO_TYPE || token->type == TYPE_S_QUOTE_STRING \
				|| token->type == TYPE_D_QUOTE_STRING)
		{
			if (!ft_strncmp("-", token->content, 1))
				token->type = TYPE_ARG_OPTION;
			else
				token->type = TYPE_ARG_STRING;
		}
		token = token->next;
	}
}
