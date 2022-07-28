/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 09:53:50 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/06/13 15:26:54 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*
 * Create a new list double of type t_list and return it
*/
t_double_list	*ft_dlstnew(int value)
{
	t_double_list	*list;

	list = (t_double_list *) ft_calloc(1, sizeof(t_double_list));
	if (!list)
		return (NULL);
	list->value = value;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}
