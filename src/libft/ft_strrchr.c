/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:24:33 by dlaidet           #+#    #+#             */
/*   Updated: 2022/03/29 14:24:35 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	int		compt;

	tmp = (char *)s;
	compt = ft_strlen(tmp);
	while (tmp[compt] >= 0 && tmp[compt] != (char)c && compt > 0)
	{
		compt--;
	}
	if (tmp[compt] == (char)c)
		return (&tmp[compt]);
	return (NULL);
}
