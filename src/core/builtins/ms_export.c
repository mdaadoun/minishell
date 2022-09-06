/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 08:46:45 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/06 07:23:52 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	check_arg(char *str)
{
	char	c;

	c = str[0];
	if (c >= 'a' && c <= 'z')
		return (0);
	else if (c >= 'A' && c <= 'Z')
		return (0);
	else if (c == '_')
		return (0);
	return (-1);
}

static void	print_env_export(t_minishell *ms)
{
	char	**envp;
	size_t	ind;
	size_t	len;

	ms_sorting_env(ms);
	envp = ms->envp;
	ind = 0;
	while (envp[ind])
	{
		ft_putstr_fd("declare -x ", 1);
		len = ft_strlen_arg(envp[ind], '=');
		ft_putnstr_fd(envp[ind], len, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(&envp[ind][len + 1], 1);
		ft_putstr_fd("\"\n", 1);
		ind++;
	}
}

static void	check_flag_error(t_minishell *ms)
{
	if (ms->global_error->flag)
		g_sig.exit_status = 1;
	else
		g_sig.exit_status = 0;
}

static void	run_export(t_minishell *ms, char **arg, size_t ind)
{
	t_variable	*env;
	t_variable	*find;

	while (arg[ind])
	{
		if (check_arg(arg[ind]) == -1)
		{
			ms_set_error(ms->global_error, ERROR_EXPORT, MSG_ERROR_EXPORT);
			ind++;
			continue ;
		}
		env = ft_create_variable(ms, arg[ind]);
		if (env != 0)
		{
			find = ft_get_struct_env(ms, env->name);
			if (find == 0)
				ft_add_variable(ms, env);
			else
				ft_replace_variable(ms, env);
		}
		ind++;
	}
}

/*
 *	set the export attribute for variables
 *  Dynamic structure of variables
 *  check for existing env
 *  replace or create new env
 */
void	ms_export(t_minishell *ms, char **arg)
{
	if (ft_count_tab_string(arg) == 1)
		print_env_export(ms);
	else
	{
		run_export(ms, arg, 1);
		ms_build_env_tab(ms);
	}
	check_flag_error(ms);
}
