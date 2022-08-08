/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:29:14 by dlaidet           #+#    #+#             */
/*   Updated: 2022/03/29 13:29:15 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*tmp;
	int		compt;

	tmp = (char *)s;
	compt = 0;
	while (tmp[compt] != '\0' && tmp[compt] != (char)c)
	{
		compt++;
	}
	if (tmp[compt] == (char)c)
		return (&tmp[compt]);
	return (NULL);
}
