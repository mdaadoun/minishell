/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:55:29 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/29 11:29:43 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void 	ms_combine_token(t_token *first_token, t_token *second_token)
{
	char	*tmp;

	first_token->no_space = second_token->no_space;
	// first_token->next = second_token->next;
	// if (second_token->next)
	// 	second_token->next->prev = first_token;
	tmp = ft_strjoin(first_token->content, second_token->content);
	free(first_token->content);
	first_token->content = tmp;
	ms_delete_token(second_token);
	// free(second_token->content);
	// free(second_token);
}