/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:46:11 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/03 15:12:01 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"


// static char	*ft_get_cmd(char **path, char *cmd)
// {
// 	char	*tmp;
// 	char	*command;

// 	while (*path)
// 	{
// 		tmp = ft_strjoin(*path, "/");
// 		command = ft_strjoin(tmp, cmd);
// 		free(tmp);
// 		if (access(command, 0) == 0)
// 			return (command);
// 		free(command);
// 		path++;
// 	}
// 	return (NULL);
// }

// rebuild each commands from tokens
void build_commands(t_minishell *ms)
{
    (void) ms;
}

// debug function to display the built commands
void display_commands(t_minishell *ms)
{
    (void) ms;
}

void ms_executer(t_minishell *ms)
{
    // if ( fork() != 0 ) // parent
    //     wait (NULL); // wait for child
    // else
    //     execve ? // execution du programme child from data
    
    // arg = ft_split(ms->full_line, ' ');
    // cmd = ft_get_cmd(ms->bin_paths, arg[0]);
    // execve(cmd, arg, envp);
    build_commands(ms);
    display_commands(ms);
}
