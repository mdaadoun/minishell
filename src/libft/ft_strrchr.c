/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:33:32 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:16:19 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*
** return last occurence of c in s 
*/
char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*cast_s;

	len = (int) ft_strlen(s);
	cast_s = (char *) s;
	while (len-- >= 0)
		if (cast_s[len + 1] == (char) c)
			return ((char *) &cast_s[len + 1]);
	return (0);
}
