/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 07:36:12 by dlaidet           #+#    #+#             */
/*   Updated: 2022/03/29 07:36:14 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	count;

	if (n == 0)
		return (0);
	count = 0;
	while (s1[count] == s2[count] && s1[count] != '\0')
	{
		if (count < (n - 1))
			count++;
		else
			return (0);
	}
	return ((unsigned char)(s1[count]) - (unsigned char)(s2[count]));
}
