/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:53:09 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:15:54 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

// # include <stdlib.h>

/*
** return a pointer to new string duplicate of s
*/
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*str;

	len = ft_strlen(s) + 1;
	str = ft_calloc(len, sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(str, s, len);
	return (str);
}
