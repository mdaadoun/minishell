/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 22:37:38 by pi                #+#    #+#             */
/*   Updated: 2022/06/29 14:41:16 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	count_nb_with_base(size_t nb, int base)
{
	int	i;

	i = 0;
	while (nb)
	{
		nb = nb / base;
		i++;
	}
	return (i);
}

static char	*get_base_set(int b, bool up)
{
	char	*tmp_set;

	if (b == 2)
		tmp_set = "01";
	else if (b == 8)
		tmp_set = "01234567";
	else if (b == 10)
		tmp_set = "0123456789";
	else if (b == 16 && up)
		tmp_set = "0123456789ABCDEF";
	else
		tmp_set = "0123456789abcdef";
	return (tmp_set);
}

/*
 * convert and return a new string from given nb to base 2, 8, 10 or 16
*/
static char	*ft_itoa_base(size_t nb, int base, bool uppercase)
{
	char	*result;
	char	*base_set;
	int		count;

	if (base != 2 && base != 8 && base != 10 && base != 16)
		return (NULL);
	count = count_nb_with_base(nb, base);
	result = NULL;
	result = (char *)malloc((count + 1) * sizeof(char));
	result[count] = '\0';
	base_set = get_base_set(base, uppercase);
	while (count--)
	{
		result[count] = base_set[nb % base];
		nb = nb / base;
	}
	return (result);
}

int	ft_putbase_pf(size_t nb, int base, bool uppercase, int *len)
{
	int		length;
	char	*str;

	length = 0;
	if (!nb)
	{
		length += ft_putchar_pf('0', len);
		return (length);
	}
	str = (void *)0;
	str = ft_itoa_base(nb, base, uppercase);
	length = ft_putstr_pf(str, len);
	free(str);
	return (length);
}
