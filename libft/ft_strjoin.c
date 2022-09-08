/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 03:57:16 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:15:59 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/* 
** join s1 and s2 in a new returned string
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*str;

	if (!s1 || !s2)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	if (!str)
		return (0);
	ft_memcpy(str, s1, len_s1);
	ft_memcpy(&str[len_s1], s2, len_s2);
	return (str);
}
