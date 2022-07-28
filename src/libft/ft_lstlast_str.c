/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:44:00 by pi                #+#    #+#             */
/*   Updated: 2022/07/13 16:55:29 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*
 * Return the last connected list by checking if next is NULL
*/
t_list_str	*ft_lstlast_str(t_list_str *lst)
{
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (lst);
}
