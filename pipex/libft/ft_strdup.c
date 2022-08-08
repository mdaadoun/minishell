/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:41:33 by dlaidet           #+#    #+#             */
/*   Updated: 2022/03/29 11:41:35 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	int		compt;
	char	*rst;

	len = ft_strlen(s);
	rst = malloc(sizeof(char) * len + 1);
	if (!rst)
		return (0);
	compt = 0;
	while (compt < len)
	{
		rst[compt] = s[compt];
		compt++;
	}
	rst[len] = '\0';
	return (rst);
}
