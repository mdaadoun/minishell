/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:45:37 by dlaidet           #+#    #+#             */
/*   Updated: 2022/03/29 10:45:39 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	b;
	size_t	c;

	if (*little == 0)
		return ((char *)big);
	b = 0;
	while (big[b] != '\0' && b < len)
	{
		c = 0;
		while (little[c] == big[b + c] && (b + c) < len)
		{
			if (little[c + 1] == '\0')
				return ((char *)(big + b));
			c++;
		}
		b++;
	}
	return (0);
}
