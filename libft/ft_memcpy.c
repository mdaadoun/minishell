/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:12:59 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:15:22 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** copies n bytes from memory area src to memory area dest.
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*cast_src;
	unsigned char	*cast_dst;

	if (!dest && !src)
		return (NULL);
	cast_dst = (unsigned char *) dest;
	cast_src = (unsigned char *) src;
	while (n--)
		*cast_dst++ = *cast_src++;
	return (dest);
}
