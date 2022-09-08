/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:45:50 by pi                #+#    #+#             */
/*   Updated: 2022/05/24 10:39:25 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

int	ft_strlen_pf(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_putchar_pf(char c, int *len)
{
	write(1, &c, 1);
	*len += 1;
	return (1);
}

int	ft_putstr_pf(char *s, int *len)
{
	int	length;

	length = 0;
	if (s)
	{
		length = ft_strlen_pf(s);
		write(1, s, length);
	}
	else
	{
		length = 6;
		write(1, "(null)", length);
	}
	*len += length;
	return (length);
}

int	ft_putnbr_pf(int n, int *len)
{
	unsigned int	nbr;

	if (n < 0)
	{
		ft_putchar_pf('-', len);
		nbr = (unsigned int)(n * -1);
	}
	else
		nbr = n;
	if (nbr >= 10)
	{
		ft_putnbr_pf(nbr / 10, len);
	}
	ft_putchar_pf('0' + nbr % 10, len);
	return (0);
}

int	ft_putpointer_pf(void *pointer, int base, int *len)
{
	int	length;

	length = 0;
	if (pointer)
	{
		length += ft_putstr_pf("0x", len);
		length += ft_putbase_pf((size_t)pointer, base, false, len);
	}
	else
	{
		length = 5;
		write(1, "(nil)", length);
		*len += length;
	}
	return (length);
}
