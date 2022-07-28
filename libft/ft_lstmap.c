/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 08:36:30 by dlaidet           #+#    #+#             */
/*   Updated: 2022/04/06 08:36:32 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rst;
	t_list	*tmp;

	rst = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (tmp == 0)
		{
			ft_lstclear(&rst, del);
			return (0);
		}
		ft_lstadd_back(&rst, tmp);
		lst = lst->next;
	}
	return (rst);
}
