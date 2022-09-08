/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 09:11:35 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/05 12:19:19 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	a;
	int	compt;

	compt = 0;
	a = 0;
	while (a == 0 && (s1[compt] != '\0' || s2[compt] != '\0'))
	{
		a = s1[compt] - s2[compt];
		compt++;
	}
	return (a);
}
