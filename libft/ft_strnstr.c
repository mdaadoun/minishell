/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:29:39 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:16:16 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/* 
** return first occurence of c-string little in c-string big
** 	search only for len characters.
** Return big if little is empty, pointer to first char in big
** 	for the first occurence of little, or 0 if nothing is found.
*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *) big);
	i = 0;
	while (len-- && big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j] && j < len + 1)
			j++;
		if (!little[j])
			return ((char *) &big[i]);
		if (!big[i + j])
			return (0);
		i++;
	}
	return (0);
}
