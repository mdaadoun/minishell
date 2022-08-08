/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 08:47:02 by dlaidet           #+#    #+#             */
/*   Updated: 2022/03/29 08:47:04 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	a;
	size_t	b;

	a = ft_strlen(src);
	b = 0;
	if (dst == NULL || src == NULL)
		return (0);
	if (size != 0)
	{
		while (src[b] != '\0' && b < size - 1)
		{
			dst[b] = src[b];
			b++;
		}
		dst[b] = '\0';
	}
	return (a);
}
