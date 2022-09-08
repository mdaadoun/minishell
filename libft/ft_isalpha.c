/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:46:23 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:14:33 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*
** checks if c is an alphabetic character with ft_isupper & ft_islower
*/
int	ft_isalpha(int c)
{
	if (ft_isupper(c) || ft_islower(c))
		return (1024);
	return (0);
}
