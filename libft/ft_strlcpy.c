/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:56:13 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:16:05 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** copy a string src to dst and return the length of the copied string
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	length;
	char	*cast_dst;
	char	*cast_src;

	cast_dst = (char *) dst;
	cast_src = (char *) src;
	length = ft_strlen(cast_src);
	if (size > length)
		size = length + 1;
	if (!size)
		return (length);
	while (--size)
		*cast_dst++ = *cast_src++;
	*cast_dst = '\0';
	return (length);
}
