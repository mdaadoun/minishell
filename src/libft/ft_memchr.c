/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:37:24 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:15:17 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*
** Scan n bytes in the memory areas of s to find the c byte.
** Return the pointer address in s to the first occurence of c.
** Return 0 if no match is found.
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*cast_s;

	cast_s = (char *) s;
	while (n--)
	{
		if (*(cast_s) == (char) c)
			return ((void *) cast_s);
		cast_s++;
	}
	return (0);
}
