/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:20:00 by dlaidet           #+#    #+#             */
/*   Updated: 2022/03/28 14:20:02 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*temp;

	if (s == NULL)
		return (NULL);
	temp = s;
	while (n != 0)
	{
		*temp = c;
		temp++;
		n--;
	}
	return (s);
}
