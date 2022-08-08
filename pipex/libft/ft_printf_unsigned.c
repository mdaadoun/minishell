/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 06:38:36 by dlaidet           #+#    #+#             */
/*   Updated: 2022/04/14 06:38:39 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_count(unsigned int nbr);

int	ft_print_unsigned(unsigned int nbr)
{
	char	*rst;
	int		len;

	len = 0;
	if (nbr == 0)
		len += write(1, "0", 1);
	else
	{
		rst = ft_unsigned_itoa(nbr);
		len += ft_printstr(rst);
		free(rst);
	}
	return (len);
}

char	*ft_unsigned_itoa(unsigned int nbr)
{
	int		len;
	char	*rst;

	len = ft_count(nbr);
	rst = malloc(sizeof(char) * len + 1);
	if (!rst)
		return (0);
	rst[len] = '\0';
	while (nbr != 0)
	{
		rst[len - 1] = nbr % 10 + 48;
		nbr = nbr / 10;
		len--;
	}
	return (rst);
}

int	ft_count(unsigned int nbr)
{
	int	len;

	len = 0;
	while (nbr != 0)
	{
		len++;
		nbr = nbr / 10;
	}
	return (len);
}
