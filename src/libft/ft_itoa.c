/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:52:09 by dlaidet           #+#    #+#             */
/*   Updated: 2022/03/31 09:52:10 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_count(int a)
{
	int	count;

	count = 0;
	while (a)
	{
		a /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int				size;
	long int		tmp;
	char			*rst;

	tmp = n;
	size = 0;
	if (n <= 0 && size++ == 0)
		tmp = -tmp;
	else
		size = 0;
	size += ft_count(n);
	rst = (char *)malloc(size + 1);
	if (rst == 0)
		return (0);
	rst[size--] = '\0';
	while (tmp)
	{
		rst[size--] = tmp % 10 + '0';
		tmp /= 10;
	}
	if (size == 0 && rst[1] == '\0')
		rst[size] = '0';
	else if (size == 0 && rst[1] != '\0')
		rst[size] = '-';
	return (rst);
}
