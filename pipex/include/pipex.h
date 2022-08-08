/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaidet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 08:09:02 by dlaidet           #+#    #+#             */
/*   Updated: 2022/06/09 08:09:04 by dlaidet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_var
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe[2];
	int		infile;
	int		outfile;
	char	**arg;
	char	*cmd;
	char	*path;
	char	**cmd_path;
}				t_var;

//main.c
void	ft_free_path(t_var *var);

//ft_arg.c
void	ft_check_arg(int ac, char **av, t_var *var);

//ft_error.c
void	ft_error(char *str);
void	ft_perror(char *str);

//ft_child.c
void	ft_first_child(t_var *var, char **av, char **envp);
void	ft_second_child(t_var *var, char **av, char **envp);

#endif
