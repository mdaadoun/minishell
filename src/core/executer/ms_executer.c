/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:46:11 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/02 15:59:59 by mdaadoun         ###   ########.fr       */
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

void ms_executer(t_minishell *ms)
{
    // if ( fork() != 0 ) // parent
    //     wait (NULL); // wait for child
    // else
    //     execve ? // execution du programme child from data
    
    // arg = ft_split(ms->line, ' ');
    // cmd = ft_get_cmd(ms->bin_paths, arg[0]);
    // execve(cmd, arg, envp);
    (void) ms;
}
