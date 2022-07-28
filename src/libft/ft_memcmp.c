/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 07:01:23 by dlaidet           #+#    #+#             */
/*   Updated: 2022/03/30 07:01:25 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				diff;

	diff = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (diff == 0 && n > 0)
	{
		diff = *str1 - *str2;
		n--;
		str1++;
		str2++;
	}
	return (diff);
}
