/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 09:03:27 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/04 07:35:13 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

 // build data structure from line 
 // read command line and build tokens structure 
 // (space "" '' $ |)
void ms_parser(t_minishell *ms)
{
	ms_parse_quotes(ms);
	ms_swap_env(ms);
	ms_parse_pipe(ms);
}