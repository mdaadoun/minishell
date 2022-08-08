/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 08:05:20 by dlaidet           #+#    #+#             */
/*   Updated: 2022/03/30 08:05:21 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static char	*ft_dup(const char *str, int start, int finish)
{
	char	*dup;
	int		count;

	count = 0;
	dup = malloc(sizeof(char) * (finish - start + 1));
	if (dup == 0)
		return (0);
	while (start < finish)
		dup[count++] = str[start++];
	dup[count] = '\0';
	return (dup);
}

static int	ft_count_tab(const char *s, char c, int tab)
{
	int	compt;
	int	sw;

	compt = 0;
	sw = 0;
	while (s[compt])
	{
		if (s[compt] != c && sw == 0)
		{
			sw = 1;
			tab++;
		}
		else if (s[compt] == c)
			sw = 0;
		compt++;
	}
	return (tab);
}

static char	**ft_fill_tab(char **rst, const char *s, char c, size_t len)
{
	size_t	a;
	size_t	b;
	int		find;

	a = 0;
	b = 0;
	find = -1;
	while (a <= len)
	{
		if (s[a] != c && find < 0)
			find = a;
		else if ((s[a] == c || a == len) && find >= 0)
		{
			rst[b++] = ft_dup(s, find, a);
			find = -1;
		}
		a++;
	}
	rst[b] = 0;
	return (rst);
}

char	**ft_split(char const *s, char c)
{
	char	**rst;
	size_t	len;

	if (s == 0)
		return (0);
	len = ft_strlen(s);
	rst = malloc(sizeof(char *) * (ft_count_tab(s, c, 0) + 1));
	if (rst == 0)
		return (0);
	rst = ft_fill_tab(rst, s, c, len);
	return (rst);
}
