/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:54:28 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:14:10 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** 	allocate memory of number*size and set each value to 0
**	return the pointer to first area of this memory
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb > 4294967296 && size > 4294967296)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
