/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:37:14 by dlaidet           #+#    #+#             */
/*   Updated: 2022/03/28 14:37:16 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

// check return condition of dest.

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	count;

	if (!dest && !src)
		return (dest);
	count = 0;
	while (count < n)
	{
		((unsigned char *)dest)[count] = ((unsigned char *)src)[count];
		count++;
	}
	return (dest);
}
