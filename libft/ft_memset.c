/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 08:49:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/06/28 10:27:21 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** Copy n times c in the memory areas of s
*/
void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*cast_s;

	cast_s = (char *) s;
	i = 0;
	while (i++ < n)
		cast_s[i - 1] = c;
	return (s);
}
