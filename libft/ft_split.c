/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 08:41:58 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:15:47 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_count_words(char *str, char sep)
{
	size_t	flag;
	size_t	i;
	size_t	found;

	if (!str)
		return (0);
	i = 0;
	found = 0;
	flag = 1;
	while (str[i])
	{
		if (flag && str[i] != sep)
		{
			found++;
			flag = 0;
		}
		if (!flag && str[i] == sep)
			flag = 1;
		i++;
	}
	return (found);
}

void	fill_words(char **array, char *str, char sep, size_t nb)
{
	size_t	index;
	size_t	length;
	size_t	flag;

	index = 0;
	length = 0;
	flag = 1;
	while (nb--)
	{
		while (str[index++] && flag != 2)
		{
			if (str[index - 1] != sep)
			{
				if (flag)
					flag = 0;
				length++;
			}
			if (!flag && str[index] == sep)
				flag = 2;
		}
		*array++ = ft_substr(str, index - length - 1, length);
		length = 0;
		flag = 1;
	}
}

/*
** return an array of strings composed with s separated by c
*/
char	**ft_split(char const *s, char c)
{
	char	**str_arr;
	size_t	words_nb;

	words_nb = ft_count_words((char *)s, c);
	str_arr = ft_calloc(words_nb + 1, sizeof(char *));
	if (!str_arr)
		return (0);
	fill_words(str_arr, (char *)s, c, words_nb);
	return (str_arr);
}
