/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 07:27:29 by dlaidet           #+#    #+#             */
/*   Updated: 2022/03/30 07:29:26 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static void	ft_cpy(char *rst, char const *s, size_t len)
{
	size_t	compt;

	compt = 0;
	while (compt < len)
	{
		rst[compt] = s[compt];
		compt++;
	}
	rst[compt] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*rst;
	size_t	lon;

	if (s == 0)
		return (0);
	lon = ft_strlen(s);
	if (len > lon)
		len = lon;
	if (start > lon)
	{
		rst = malloc(sizeof(char) * len);
		rst[0] = '\0';
		return (rst);
	}
	else
	{
		lon = ft_strlen(&s[start]);
		if (len > lon)
			len = lon;
		rst = malloc(sizeof(char) * len + 1);
		if (rst == NULL)
			return (NULL);
		ft_cpy(rst, &s[start], len);
	}
	return (rst);
}
