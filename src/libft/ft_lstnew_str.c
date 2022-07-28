/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 09:53:50 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/07/13 16:56:11 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*
 * Create a new list of type t_list_value and return it
*/
t_list_str	*ft_lstnew_str(char *str)
{
	t_list_str	*list;

	list = ft_calloc(1, sizeof(t_list_str));
	if (!list)
		return (NULL);
	list->str = str;
	list->next = NULL;
	return (list);
}
