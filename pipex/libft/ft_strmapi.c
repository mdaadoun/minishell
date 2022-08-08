/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 09:40:05 by dlaidet           #+#    #+#             */
/*   Updated: 2022/04/02 09:40:08 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	count;
	char			*rst;

	if (s == 0 || f == 0)
		return (0);
	rst = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (rst == 0)
		return (0);
	ft_strlcpy(rst, s, ft_strlen(s) + 1);
	count = 0;
	while (rst[count])
	{
		rst[count] = (*f)(count, rst[count]);
		count++;
	}
	return (rst);
}
