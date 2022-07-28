/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 07:23:53 by dlaidet           #+#    #+#             */
/*   Updated: 2022/03/30 07:23:12 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*dest;

	if (s1 == 0 || s2 == 0)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * len + 1);
	if (!dest)
		return (0);
	len = ft_strlcpy(dest, s1, ft_strlen(s1) + 1);
	len = ft_strlcpy(&dest[len], s2, ft_strlen(s2) + 1);
	return (dest);
}
