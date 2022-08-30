/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:28:14 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/30 07:26:58 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static t_variable	*get_struct_env(t_variable *env, char *name, size_t len)
{
	while (env)
	{
		if (!ft_strncmp(env->name, name, len))
			break ;
		env = env->next;
	}
	return (env);
}

static void	update_pwd(t_minishell *ms)
{
	t_variable	*old;
	char		cwd[PATH_MAX];

	old = get_struct_env(ms->first_var, "OLDPWD", 7);
	free(old->content);
	old->content = ms->cwd_path;
	ms->cwd_path = ft_strdup(getcwd(cwd, PATH_MAX));
}

static bool	args_are_valid(t_minishell *ms, char **arg)
{
	int			i;
	t_err_key	err_key;
	char		*err_msg;

	err_key = ERROR_EXTRA_ARGS;
	err_msg = MSG_ERROR_EXTRA_ARGS;
	i = 0;
	while (arg[i])
		i++;
	if (i > 2)
	{
		ms_set_error(ms->global_error, err_key, err_msg);
		return (false);
	}
	return (true);
}

t_uint8	ms_cd(t_minishell *ms, char **arg)
{
	int			ret;
	t_variable	*env;

	if (!args_are_valid(ms, arg))
		return (1);
	else if (!arg[1] || !ft_strncmp(arg[1], "~", 2))
	{
		env = get_struct_env(ms->first_var, "HOME", 5);
		ret = chdir(env->content);
		update_pwd(ms);
	}
	else if (!strncmp(arg[1], "-", 2))
	{
		env = get_struct_env(ms->first_var, "OLDPWD", 7);
		ret = chdir(env->content);
		update_pwd(ms);
	}
	else
	{
		ret = chdir(arg[1]);
		if (ret == 0)
			update_pwd(ms);
	}
	if (ret != 0)
		ms_set_error(ms->global_error, ERROR_PATH, MSG_ERROR_PATH);
	return (ret);
}
