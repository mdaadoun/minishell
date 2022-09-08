/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:21:51 by pi                #+#    #+#             */
/*   Updated: 2022/07/13 17:46:35 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
 * free all connected lists and set the initial pointer to NULL
*/
void	ft_lstclear_str(t_list_str **lst, void (*del)(char *))
{
	t_list_str	*next;

	if (!lst || !del || !*lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone_str(*lst, del);
		*lst = next;
	}
}
