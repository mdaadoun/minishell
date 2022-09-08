/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:51:42 by pi                #+#    #+#             */
/*   Updated: 2022/06/29 14:43:44 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
 * set the last connected element of list lst to new
 * 1. the last get new list as the next
 * 2. the new list become the last and replace the prev of the first list 
*/
void	ft_dlstadd_back(t_double_list *first, t_double_list *new)
{
	t_double_list	*last;

	if (!first || !new)
		return ;
	last = ft_dlstlast(first);
	last->next = new;
	first->prev = new;
	new->prev = last;
	new->next = first;
}
