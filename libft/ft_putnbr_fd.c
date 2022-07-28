/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 09:29:01 by dlaidet           #+#    #+#             */
/*   Updated: 2022/04/02 09:29:03 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	a;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		a = n * -1;
	}
	else
		a = n;
	if (a > 9)
		ft_putnbr_fd((a / 10), fd);
	ft_putchar_fd((char)(a % 10 + 48), fd);
}
