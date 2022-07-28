/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:12:25 by dlaidet           #+#    #+#             */
/*   Updated: 2022/03/29 10:12:28 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	a;
	size_t	b;

	a = ft_strlen(src);
	b = ft_strlen(dst);
	if (size <= b)
		return (size + a);
	a = 0;
	while (src[a] != '\0' && b + a + 1 < size)
	{
		dst[b + a] = src[a];
		a++;
	}
	dst[b + a] = '\0';
	return (ft_strlen(&src[a]) + ft_strlen(dst));
}
