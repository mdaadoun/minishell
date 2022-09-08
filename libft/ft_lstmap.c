/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:56:27 by pi                #+#    #+#             */
/*   Updated: 2022/07/12 09:18:01 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
 *  Apply the function f to the content of each connected lists
 *      Return a new connected list with the modified content
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_elem;

	if (!lst || !f)
		return (0);
	new_elem = 0;
	new_list = 0;
	while (lst)
	{
		new_elem = ft_lstnew(f(lst->content));
		if (!new_elem)
			ft_lstclear(&new_elem, del);
		else if (!new_list)
			new_list = new_elem;
		else
			ft_lstadd_back(&new_list, new_elem);
		lst = lst->next;
	}
	return (new_list);
}
