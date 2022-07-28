/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:32:20 by dlaidet           #+#    #+#             */
/*   Updated: 2022/03/29 15:32:22 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;

	if (nmemb > 4294967296 && size > 4294967296)
		return (0);
	s = malloc(size * nmemb);
	if (s == 0)
		return (0);
	ft_bzero(s, (nmemb * size));
	return (s);
}
