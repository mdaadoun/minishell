/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:13:08 by pi                #+#    #+#             */
/*   Updated: 2022/07/13 17:43:49 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
 *  Pass the content of lst to the function del and then free it
*/
void	ft_lstdelone_str(t_list_str *lst, void (*del)(char *))
{
	if (!lst || !del)
		return ;
	del(lst->str);
	free(lst);
}
