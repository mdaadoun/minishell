/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:55:29 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/30 11:19:39 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	ms_combine_token(t_token *first_token, t_token *second_token)
{
	char	*tmp;

	first_token->no_space = second_token->no_space;
	tmp = ft_strjoin(first_token->content, second_token->content);
	free(first_token->content);
	first_token->content = tmp;
	ms_delete_token(second_token);
}

/*
 *	Free all the process allocated memory and print error message if any.
 *
 *	@params:
 *		ms : the main minishell data structure to free.
 *	@return:
 *		EXIT_SUCCESS or EXIT_FAILURE depending error.
 */
int	ms_free_before_exit(t_minishell *ms)
{
	if (ms)
	{
		if (ms->cwd_path)
			free(ms->cwd_path);
		ms_free_last_command(ms);
		ms_free_env(ms);
		if (ms->envp)
			ms_free_envp(ms->envp);
		if (ms->global_error->flag)
		{
			write(2, ms->global_error->msg, ms->global_error->length);
			write(2, "\n", 1);
			free(ms);
			return (EXIT_FAILURE);
		}
		free(ms);
	}
	return (EXIT_SUCCESS);
}
