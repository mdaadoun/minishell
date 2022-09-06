/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_is.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:40:46 by dlaidet           #+#    #+#             */
/*   Updated: 2022/09/06 10:59:21 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// Return true if all the token are empty with space
bool	is_empty_command(t_minishell *ms)
{
	t_token	*token;
	int		i;

	token = ms->first_token;
	while (token)
	{
		i = 0;
		while (token->content[i])
		{
			if (token->content[i] != ' ')
				return (false);
			i++;
		}
		token = token->next;
	}
	return (true);
}

bool	is_builtin_fork(t_builtins built)
{
	if (built == BIN_CD)
		return (false);
	if (built == BIN_EXPORT)
		return (false);
	if (built == BIN_UNSET)
		return (false);
	if (built == BIN_EXIT)
		return (false);
	return (true);
}

int	is_redirect(t_token *tok)
{
	if (tok->type == TYPE_REDIRECT_LEFT)
		return (4);
	else if (tok->type == TYPE_REDIRECT_RIGHT)
		return (3);
	else if (tok->type == TYPE_REDIRECT_DOUBLE_RIGHT)
		return (2);
	else if (tok->type == TYPE_REDIRECT_DOUBLE_LEFT)
		return (1);
	return (0);
}

bool	is_builtin(t_token *command, char *name_bin, t_builtins index_bin)
{
	if (!ft_strncmp(name_bin, command->content, ft_strlen(name_bin) + 1))
	{
		command->builtin = index_bin;
		return (true);
	}
	return (false);
}

bool	check_if_builtin(t_token *command)
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
