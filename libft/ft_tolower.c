/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 10:54:27 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:16:27 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** convert c char if uppercase to lowercase
*/
int	ft_tolower(int c)
{
	if (ft_isupper(c))
		c += 32;
	return (c);
}
