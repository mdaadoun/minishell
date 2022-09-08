/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 10:54:27 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:16:29 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** convert c char if lowercase to uppercase
*/
int	ft_toupper(int c)
{
	if (ft_islower(c))
		c -= 32;
	return (c);
}
