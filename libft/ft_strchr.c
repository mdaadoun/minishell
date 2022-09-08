/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:33:32 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:15:51 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
** return first occurence of c byte in c-string s.
*/
char	*ft_strchr(const char *s, int c)
{
	return ((char *) ft_memchr((void *) s, c, ft_strlen(s) + 1));
}
