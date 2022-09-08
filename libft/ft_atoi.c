/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:56:37 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:14:04 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*
** converts the c-string nptr to int.
** -48 is ascii offset for char 0
*/
int	set_neg(int isneg, int nb)
{
	if (isneg)
		return (-nb);
	else
		return (nb);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	isneg;
	int	ispos;

	result = 0;
	isneg = 0;
	ispos = 0;
	while (*nptr++)
	{
		if (ft_isspace(*(nptr - 1)) && !result && !ispos && !isneg)
			;
		else if (*(nptr - 1) == '+' && !result && !ispos && !isneg)
			ispos = 1;
		else if (*(nptr - 1) == '-' && !result && !ispos && !isneg)
			isneg = 1;
		else if (ft_isdigit(*(nptr - 1)))
			result = result * 10 + *(nptr - 1) - 48;
		else
			return (set_neg(isneg, result));
	}
	return (set_neg(isneg, result));
}
