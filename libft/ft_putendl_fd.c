/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 12:01:56 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:15:38 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	length;

	if (s)
	{
		length = ft_strlen(s);
		write(fd, s, length);
		write(fd, "\n", 1);
	}
}
