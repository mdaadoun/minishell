/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 08:38:02 by dlaidet           #+#    #+#             */
/*   Updated: 2022/06/09 08:38:04 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_error(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	exit(-1);
}

void	ft_perror(char *str)
{
	perror(str);
	exit(-1);
}
