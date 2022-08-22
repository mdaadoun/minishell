/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:28:14 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/22 14:33:01 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static t_variable	*get_struct_env(t_variable *env, char *name, size_t len)
{
	while (env)
	{
		if (!ft_strncmp(env->name, name, len))
			break;
		env = env->next;
	}
	return (env);
}

static void	update_old_pwd(t_minishell *ms)
{
	t_variable	*env;
	t_variable	*tmp;

	tmp = get_struct_env(ms->first_var, "OLDPWD", 7);
	env = get_struct_env(ms->first_var, "PWD", 4);
	free(tmp->content);
	tmp->content = ft_strdup(env->content);
}

/*
 *	change the working directory
 *	update env OLDPWD
 *	chdir for new working directory
 */
t_uint8	ms_cd(t_minishell *ms, char **arg)
{
	int	ret;
	t_variable	*env;
	char	*str;

	if (!arg[1] || !ft_strncmp(arg[1], "~", 2))
	{
		//look for '~'
		env = get_struct_env(ms->first_var, "HOME", 5);
		update_old_pwd(ms);
		ret = chdir(env->content);
		free(ms->cwd_path);
		ms->cwd_path = ft_strdup(env->content);
	}
	if (!strncmp(arg[1], "-", 2))
	{
		env = get_struct_env(ms->first_var, "OLDPWD", 5);
		str = ft_strdup(env->content);
		update_old_pwd(ms);
		ret = chdir(str);
		free(ms->cwd_path);
		ms->cwd_path = str;
	}
	else
	{
		update_old_pwd(ms);
		ret = chdir(arg[1]);
//		free(ms->cwd_path);
//		env = get_struct_env(ms->first_var, "PWD", 4);
//		ms->cwd_path = ft_strdup(env->content);
	}
	if (ret != 0)
		ft_printf("TODO: Printf Error cd builtin\n");
	return (ret);
}
