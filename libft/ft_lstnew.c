/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 08:23:31 by dlaidet           #+#    #+#             */
/*   Updated: 2022/04/05 08:23:33 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ind;

	ind = malloc(sizeof(t_list));
	if (ind == 0)
		return (0);
	ind->content = content;
	ind->next = 0;
	return (ind);
}
