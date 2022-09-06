/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_analyze_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:43:46 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/06 10:37:12 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static bool	is_builtin(t_token *command, char *name_bin, t_builtins index_bin)
{
	if (!ft_strncmp(name_bin, command->content, ft_strlen(name_bin) + 1))
	{
		command->builtin = index_bin;
		return (true);
	}
	return (false);
}

static bool	check_if_builtin(t_token *command)
{
	bool	flag;

	flag = false;
	if (is_builtin(command, "cd", BIN_CD))
		flag = true;
	else if (is_builtin(command, "echo", BIN_ECHO))
		flag = true;
	else if (is_builtin(command, "export", BIN_EXPORT))
		flag = true;
	else if (is_builtin(command, "env", BIN_ENV))
		flag = true;
	else if (is_builtin(command, "exit", BIN_EXIT))
		flag = true;
	else if (is_builtin(command, "pwd", BIN_PWD))
		flag = true;
	else if (is_builtin(command, "unset", BIN_UNSET))
		flag = true;
	if (flag)
	{
		command->type = TYPE_BUILTIN_COMMAND;
		return (true);
	}
	return (false);
}

static bool	check_absolute_path(t_token *command)
{
	char	*command_path;

	if (command->content[0] == '/' || command->content[0] == '~')
	{
		command_path = strdup(command->content);
		if (access(command_path, 0) == 0)
		{
			command->type = TYPE_EXTERNAL_COMMAND;
			command->external_path = command_path;
			return (true);
		}
		free(command_path);
	}
	return (false);
}

/*
 * If the token is an external command:
 *      The type of token become TYPE_EXTERNAL_COMMAND
 *      The content of token become the path to the external command
 */
static bool	check_if_external(t_minishell *ms, t_token *command)
{
	char	*tmp_path;
	char	*command_path;
	char	**path;
	int		i;

	i = 0;
	if (check_absolute_path(command) == true)
		return (true);
	path = ft_split(ft_get_env(ms, "PATH"), ':');
	while (path[i])
	{
		tmp_path = ft_strjoin(path[i], "/");
		command_path = ft_strjoin(tmp_path, command->content);
		free(tmp_path);
		if (access(command_path, 0) == 0)
		{
			command->type = TYPE_EXTERNAL_COMMAND;
			if (command->external_path)
				free (command->external_path);
			command->external_path = command_path;
			ms_free_double_pointer(path);
			return (true);
		}
		else
			free(command_path);
		i++;
	}
	ms_free_double_pointer(path);
	return (false);
}

// check if the command is external or builtin, 
//      * tag correct type, return true
//      * error, return false
void	ms_analyze_command(t_minishell *ms, t_token *cmd)
{
	t_token	*command;

	command = cmd;
	if (command && !ms_is_redirection(command))
	{
		check_if_builtin(command);
		if (command->type == TYPE_PIPE)
		{
			g_sig.exit_status = 2;
			ms_set_error(ms->global_error, ERROR_SYNTAX, MSG_ERROR_SYNTAX_PIPE);
		}
		if (command->type != TYPE_BUILTIN_COMMAND)
			check_if_external(ms, command);
		if (command->type != TYPE_EXTERNAL_COMMAND \
				&& command->type != TYPE_BUILTIN_COMMAND)
			command->type = TYPE_BAD_COMMAND;
	}
}
