/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:43:46 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/04 09:31:11 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static bool is_builtin(t_token *command, char *name_bin, t_builtins index_bin)
{
    if (!ft_strncmp(name_bin, command->content, ft_strlen(command->content)))
    {
        command->builtin = index_bin;
        return (true);
    }
    return (false);
}

static bool check_if_builtin(t_token *command)
{
    bool flag;

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
    else if (is_builtin(command, "unset", BIN_UNSET))
        flag = true;
    if (flag)
    {
        command->type = BUILTIN_COMMAND;
        return (true);
    }
    return (false);
}

/*
 * If the token is an external command:
 *      The type of token become EXTERNAL_COMMAND
 *      The content of token become the path to the external command
*/
static bool check_if_external(t_minishell *ms, t_token *command)
{
    char	*tmp_path;
	char	*command_path;
    char    **path;

    path = ms->bin_paths;
	while (*path)
	{
		tmp_path = ft_strjoin(*path, "/");
		command_path = ft_strjoin(tmp_path, command->content);
		free(tmp_path);
		if (access(command_path, 0) == 0)
        {
            command->type = EXTERNAL_COMMAND;
            free(command->content);
            command->content = command_path;
			return (true);
        }
		path++;
	}
    return (false);
}

// check if the command is external or builtin, 
//      * tag correct type, return true
//      * error, return false
bool ms_is_valid_command(t_minishell *ms)
{
    bool    valid;
    t_token *command;

    command = ms->first_token;
    valid = false;
    if (check_if_builtin(command))
        valid = true;
    else if (check_if_external(ms, command))
        valid = true;
    if (valid)
        ft_printf("%s is a valid command of type %d.\n", command->content, command->type);
    else
        ft_printf("%s is not a valid command.\n", command->content);
    return (valid);
}