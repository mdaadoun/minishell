/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 06:54:22 by dlaidet           #+#    #+#             */
/*   Updated: 2022/04/14 06:54:23 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_print_hexa(unsigned int nbr, const char str)
{
	if (nbr == 0)
		return (write(1, "0", 1));
	else
		ft_put_hexa(nbr, str);
	return (ft_hexa_len(nbr));
}

int	ft_hexa_len(unsigned int nbr)
{
	int	len;

	len = 0;
	while (nbr != 0)
	{
		len++;
		nbr = nbr / 16;
	}
	return (len);
}

void	ft_put_hexa(unsigned int nbr, const char str)
{
	if (nbr >= 16)
	{
		ft_put_hexa(nbr / 16, str);
		ft_put_hexa(nbr % 16, str);
	}
	else
	{
		if (nbr <= 9)
			ft_printchar(nbr + '0');
		else
		{
			if (str == 'x')
				ft_printchar(nbr - 10 + 'a');
			if (str == 'X')
				ft_printchar(nbr - 10 + 'A');
		}
	}
}
