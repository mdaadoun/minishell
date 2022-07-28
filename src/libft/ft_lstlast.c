/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:44:00 by pi                #+#    #+#             */
/*   Updated: 2022/05/24 11:15:06 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*
 * Return the last connected list by checking if next is NULL
*/
t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (lst);
}
