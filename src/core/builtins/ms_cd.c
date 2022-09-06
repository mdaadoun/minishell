/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:28:14 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/06 13:30:50 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	update_pwd(char *path, t_minishell *ms, bool swap)
{
	t_variable	*env;
	t_variable	*old;
	char		cwd[PATH_MAX];

	env = ft_get_struct_env(ms, "PWD");
	old = ft_get_struct_env(ms, "OLDPWD");
	if (env && old)
	{
		if (!swap)
			free(old->content);
		old->content = env->content;
		if (path)
			env->content = path;
		else
			env->content = ft_strdup(getcwd(cwd, PATH_MAX));
	}
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
		g_sig.exit_status = 1;
		return (false);
	}
	return (true);
}

static int	bonus_cd(t_minishell *ms, char **arg, char *var, bool flag)
{
	int			ret;
	t_variable	*env;
	char		*path;

	env = ft_get_struct_env(ms, var);
	if (env)
	{
		if (flag == true)
		{
			if (arg[1])
				path = ft_strjoin(env->content, &arg[1][1]);
			else
				path = ft_strjoin(env->content, "");
			ret = chdir(path);
			update_pwd(path, ms, false);
		}
		else
		{
			ret = chdir(env->content);
			write(1, env->content, ft_strlen(env->content));
			write(1, "\n", 1);
			update_pwd(env->content, ms, true);
		}
	}
	return (ret);
}

void	ms_cd(t_minishell *ms, char **arg)
{
	int	ret;

	if (args_are_valid(ms, arg))
	{
		if (!arg[1] || !ft_strncmp(arg[1], "~", 1))
			ret = bonus_cd(ms, arg, "HOME", true);
		else if (!strncmp(arg[1], "-", 2))
			ret = bonus_cd(ms, arg, "OLDPWD", false);
		else
		{
			ret = chdir(arg[1]);
			if (ret == 0)
				update_pwd(NULL, ms, false);
		}
		if (ret != 0)
		{
			ms_set_error(ms->global_error, ERROR_PATH, MSG_ERROR_PATH);
			g_sig.exit_status = 1;
		}
		else
			g_sig.exit_status = 0;
	}
}
