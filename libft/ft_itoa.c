/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 08:55:02 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:14:50 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	count_chars(int n)
{
	size_t	count;

	count = 0;
	if (n == 0 || n < 0)
		count++;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

void	fill_chars(char *chars, size_t	nb_chars, int nb)
{
	size_t	unb;

	unb = 0;
	if (nb == 0)
		chars[0] = '0';
	else if (nb < 0)
	{
		chars[0] = '-';
		unb = (size_t) nb * -1;
	}
	else
		unb = nb;
	while (nb_chars)
	{
		nb_chars--;
		if (chars[nb_chars] != '-')
		{
			chars[nb_chars] = '0' + unb % 10;
			unb /= 10;
		}
	}
}

/*
**	return a string converted from the given int n
*/
char	*ft_itoa(int n)
{
	char	*str;
	size_t	nb_chars;

	nb_chars = count_chars(n);
	str = ft_calloc(nb_chars + 1, sizeof(char));
	if (!str)
		return (0);
	fill_chars(str, nb_chars, n);
	return (str);
}
