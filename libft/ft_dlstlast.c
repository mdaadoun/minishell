/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstlast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:44:00 by pi                #+#    #+#             */
/*   Updated: 2022/06/29 14:43:19 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
 * Return the last linked list by checking if next is NULL
 * Or, if circular, check if the next is equal to the first
*/
t_double_list	*ft_dlstlast(t_double_list *lst)
{
	t_double_list	*first;

	first = lst;
	while (lst || lst->next != first)
	{
		if (!lst->next || lst->next == first)
			break ;
		lst = lst->next;
	}
	return (lst);
}
