/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:45:50 by pi                #+#    #+#             */
/*   Updated: 2022/05/24 10:46:26 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

static int	check_format(const char *format, va_list arg, int *length)
{
	int		forward;

	forward = 2;
	format++;
	if (*format == '%')
		ft_putchar_pf(*format, length);
	else if (*format == 'd' || *format == 'i')
		ft_putnbr_pf(va_arg(arg, int), length);
	else if (*format == 'c')
		ft_putchar_pf(va_arg(arg, int), length);
	else if (*format == 's')
		ft_putstr_pf(va_arg(arg, char *), length);
	else if (*format == 'o')
		ft_putbase_pf(va_arg(arg, unsigned int), 8, false, length);
	else if (*format == 'u')
		ft_putbase_pf(va_arg(arg, unsigned int), 10, false, length);
	else if (*format == 'X')
		ft_putbase_pf(va_arg(arg, unsigned int), 16, true, length);
	else if (*format == 'x')
		ft_putbase_pf(va_arg(arg, unsigned int), 16, false, length);
	else if (*format == 'p')
		ft_putpointer_pf(va_arg(arg, void *), 16, length);
	return (forward);
}

/*
	forward = the number of char to move forward the parsing
*/
static int	parse_and_write_line(const char *format, va_list arg)
{
	int	length;
	int	forward;

	length = 0;
	forward = 0;
	while (*format)
	{
		if (*format == '%')
			forward = check_format(format, arg, &length);
		else
			forward = ft_putchar_pf(*format, &length);
		format = format + forward;
	}
	return (length);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		length;

	length = 0;
	va_start(arg, format);
	length = parse_and_write_line(format, arg);
	va_end(arg);
	return (length);
}
