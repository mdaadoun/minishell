/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:08:22 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:16:25 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*
**	Return a pointer to new c-string extracted from c-string s
**		of length len starting from char s[start]
**	3 if-checks:
**		1. Reset start index to end of s if start > s_len (s length)
**		2. Reset len new c-string to (s_len + start) when (len + start > s_len)
**		3. If start == s length and len is not 0, decrease len by one
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	if (start > s_len)
		start = s_len;
	if (start + len > s_len)
		len = s_len - start;
	if (start == s_len && len)
		len--;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	while (i < len)
		str[i++] = s[start++];
	return (str);
}
