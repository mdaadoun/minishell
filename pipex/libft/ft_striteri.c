/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 07:19:40 by dlaidet           #+#    #+#             */
/*   Updated: 2022/04/04 07:19:42 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	count;
	unsigned int	len;

	count = 0;
	if (s != NULL && f != NULL)
	{
		len = ft_strlen(s);
		while (count < len)
		{
			(*f)(count, &s[count]);
			count++;
		}
	}
}
