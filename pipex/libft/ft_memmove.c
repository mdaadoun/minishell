/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 07:07:22 by dlaidet           #+#    #+#             */
/*   Updated: 2022/03/29 07:07:24 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*dest;
	const char	*sourc;
	int			compt;

	if (dst == NULL || src == NULL)
		return (NULL);
	dest = (char *)dst;
	sourc = (char *)src;
	compt = 0;
	if (dst > src)
	{
		while (n--)
			dest[n] = sourc[n];
	}
	else if (src > dst)
	{
		while (n)
		{
			dest[compt] = sourc[compt];
			compt++;
			n--;
		}
	}
	return (dest);
}
