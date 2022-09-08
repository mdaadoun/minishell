/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:51:42 by pi                #+#    #+#             */
/*   Updated: 2022/07/13 16:54:34 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
 * set the last connected element of list lst to new
*/
void	ft_lstadd_back_str(t_list_str **lst, t_list_str *new)
{
	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
		(ft_lstlast_str(*lst))->next = new;
}
