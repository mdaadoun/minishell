/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 07:04:36 by dlaidet           #+#    #+#             */
/*   Updated: 2022/04/13 07:04:39 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_printf(const char *str, ...)
{
	int		count;
	int		len;
	va_list	args;

	va_start(args, str);
	count = 0;
	len = 0;
	while (str[count])
	{
		if (str[count] == '%')
		{
			len += ft_check(args, str[count + 1]);
			count++;
		}
		else
			len += ft_printchar(str[count]);
		count++;
	}
	va_end(args);
	return (len);
}

int	ft_check(va_list args, const char var)
{
	int	len;

	len = 0;
	if (var == 'c')
		len += ft_printchar(va_arg(args, int));
	else if (var == 's')
		len += ft_printstr(va_arg(args, char *));
	else if (var == 'p')
		len += ft_print_ptr(va_arg(args, unsigned long long));
	else if (var == 'i' || var == 'd')
		len += ft_printnbr(va_arg(args, int));
	else if (var == 'u')
		len += ft_print_unsigned(va_arg(args, unsigned int));
	else if (var == 'x' || var == 'X')
		len += ft_print_hexa(va_arg(args, unsigned int), var);
	else if (var == '%')
		len += ft_printpercent();
	return (len);
}
