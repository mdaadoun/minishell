/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:28:14 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/31 11:37:17 by mdaadoun         ###   ########.fr       */
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

static void	update_pwd(char *path, t_minishell *ms, bool swap)
{
	t_variable	*env;
	t_variable	*old;
	char		cwd[PATH_MAX];

	env = get_struct_env(ms->first_var, "PWD", 4);
	old = get_struct_env(ms->first_var, "OLDPWD", 7);
	if (!swap)
		free(old->content);
	old->content = env->content;
	if (path)
		env->content = path;
	else
		env->content = ft_strdup(getcwd(cwd, PATH_MAX));
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
	char		*path;

	if (!args_are_valid(ms, arg))
		return (1);
	else if (!arg[1] || !ft_strncmp(arg[1], "~", 1))
	{
		env = get_struct_env(ms->first_var, "HOME", 5);
		path = ft_strjoin(env->content, &arg[1][1]);
		ret = chdir(path);
		update_pwd(path, ms, false);
	}
	else if (!strncmp(arg[1], "-", 2))
	{
		env = get_struct_env(ms->first_var, "OLDPWD", 7);
		ret = chdir(env->content);
		write(1, env->content, ft_strlen(env->content));
		write(1, "\n", 1);
		update_pwd(env->content, ms, true);
	}
	else
	{
		ret = chdir(arg[1]);
		if (ret == 0)
			update_pwd(NULL, ms, false);
	}
	if (ret != 0)
		ms_set_error(ms->global_error, ERROR_PATH, MSG_ERROR_PATH);
	return (ret);
}
