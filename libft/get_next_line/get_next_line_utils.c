/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:07:38 by pi                #+#    #+#             */
/*   Updated: 2022/05/24 11:13:52 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/* 
    return the index of first '\n' in str or str length if '\n' not found
	ignore is used to get only the length whatever
*/
size_t	eol_or_length(const char *str, int ignore)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ignore && str[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

/*
** copies n bytes from memory area src to memory area dest.
*/
void	*ft_memcpy_gnl(void *dest, const void *src, size_t n)
{
	unsigned char	*cast_src;
	unsigned char	*cast_dst;

	if (!dest && !src)
		return (NULL);
	cast_dst = (unsigned char *) dest;
	cast_src = (unsigned char *) src;
	while (n--)
		*cast_dst++ = *cast_src++;
	return (dest);
}

/*
** join s1 and s2 in a new returned string
*/
char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*str;

	if (!s1 || !s2)
		return (0);
	len_s1 = eol_or_length(s1, 1);
	len_s2 = eol_or_length(s2, 1);
	str = NULL;
	str = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!str)
		return (0);
	str[len_s1 + len_s2] = '\0';
	ft_memcpy_gnl(str, s1, len_s1);
	ft_memcpy_gnl(&str[len_s1], s2, len_s2);
	return (str);
}

/*
**	Return a pointer to new c-string extracted from c-string s
**		of length len starting from char s[start]
**	3 if-checks:
**		1. Reset start index to end of s if start > s_len (s length)
**		2. Reset len new c-string to (s_len + start) when (len + start > s_len)
**		3. If start == s length and len is not 0, decrease len by one
*/
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	s_len = eol_or_length(s, 1);
	if (start > s_len)
		start = s_len;
	if (start + len > s_len)
		len = s_len - start;
	if (start == s_len && len)
		len--;
	str = NULL;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	str[len] = '\0';
	while (i < len)
		str[i++] = s[start++];
	return (str);
}

char	*free_and_return(char **storage, char **line, char **buffer)
{
	free(*storage);
	*storage = 0;
	free(*buffer);
	if (eol_or_length(*line, 1))
		return (*line);
	free(*line);
	return (NULL);
}
