/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:17:17 by dlaidet           #+#    #+#             */
/*   Updated: 2022/04/01 13:17:19 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static size_t	ft_trimadd(char const *s1, char const *set)
{
	size_t	count;
	size_t	ind;

	ind = 0;
	count = 0;
	while (ind < ft_strlen(s1) && count < ft_strlen(set))
	{
		if (s1[ind] == set[count])
		{
			count = 0;
			ind++;
		}
		else
			count++;
	}
	return (ind);
}

static size_t	ft_trimback(char const *s1, char const *set, size_t ind)
{
	size_t	count;

	count = 0;
	while (set[count] && ind > 0)
	{
		if (s1[ind] == set[count])
		{
			count = 0;
			ind--;
		}
		else
			count++;
	}
	return (ind);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*sta;
	char	*end;
	size_t	ind;
	size_t	len;

	len = 0;
	if (s1 == 0)
		return (0);
	ind = ft_trimadd(s1, set);
	sta = (char *)&s1[ind];
	len = ind;
	while (s1[ind])
		ind++;
	ind--;
	ind = ft_trimback(s1, set, ind);
	if (ind < len)
		len = 0;
	else
		len = (ind - len) + 1;
	end = malloc(sizeof(char) * len + 1);
	ft_strlcpy(end, sta, len + 1);
	return (end);
}
