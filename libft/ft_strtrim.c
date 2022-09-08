/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 08:07:34 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:16:22 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
 * return 1 if the char c is in the string set
*/
size_t	ft_char_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i++])
		if (set[i - 1] == c)
			return (1);
	return (0);
}

/*
 * trim the start and the end of s1 c-string using the characters set
 *	return the new str c-string
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	i = 0;
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_char_in_set(s1[start], set))
		start++;
	while (end > start && ft_char_in_set(s1[end - 1], set))
		end--;
	str = (char *) ft_calloc((end - start + 1), sizeof(char));
	if (!str)
		return (0);
	while (start < end)
		str[i++] = s1[start++];
	return (str);
}
