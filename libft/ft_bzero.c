/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:52:10 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/05/24 11:14:08 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
**	memset s string for n bytes with 0 as default value.
*/
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
