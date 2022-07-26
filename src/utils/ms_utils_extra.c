/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:55:29 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/13 07:27:22 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_free_double_pointer(char **data)
{
	size_t	ind;

	ind = 0;
	while (data[ind])
	{
		free(data[ind]);
		ind++;
	}
	free(data);
}

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
	int	ret;

	ret = g_sig.exit_status;
	if (ms)
	{
		ms_free_last_command(ms);
		ms_free_env(ms);
		if (ms->envp)
			ms_free_double_pointer(ms->envp);
		if (ms->global_error->flag && ms->global_error->key != ERROR_SILENT)
		{
			write(2, "\e[0;31mError: ", 14);
			write(2, ms->global_error->msg, ms->global_error->length);
			write(2, "\e[m\n", 4);
			free(ms);
			return (ret);
		}
		free(ms);
	}
	return (ret);
}

t_variable	*ft_get_struct_env(t_minishell *ms, char *str)
{
	t_variable	*env;

	env = ms->first_var;
	while (env)
	{
		if (ft_strlen(env->name) != ft_strlen(str))
		{
			env = env->next;
			continue ;
		}
		if (!ft_strncmp(env->name, str, ft_strlen(env->name)))
			return (env);
		env = env->next;
	}
	return (0);
}

void	ft_protect_malloc(t_minishell *ms, void *ptr)
{
	if (!ms && !ptr)
		exit(1);
	if (!ptr)
	{
		ms_set_error(ms->global_error, ERROR_MALLOC, MSG_ERROR_MALLOC);
		exit(ms_free_before_exit(ms));
	}
}
