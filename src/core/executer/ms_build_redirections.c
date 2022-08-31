/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_build_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:12:25 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/31 11:51:21 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"


static void add_heredoc_line(char *line)
{
	int fd;

	fd = open(".heredoc", O_CREAT|O_WRONLY|O_APPEND, 0777);
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	close(fd);
}

/*
 *	The heredoc loop:
 *		get the delimiter, and wait for the delimiter
 *		each line are added to a temporary file .heredoc
*/
static void open_heredoc(t_token *token)
{
	char	*line;
	char	*delimiter;
	int		check;

	delimiter = token->next->content;
	line = "";
	check = 1;
	unlink(".heredoc");
	while (check)
	{
		line = readline("> ");
		if (!line)
			break;
		check = ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1);
		if (!check)
			break;
		add_heredoc_line(line);
		free(line);
	}
}

/*
 *	First check if the current token is a redirection operator.
 *	Then check differents operators:
 *		1. >>
 *		2. <<
			if there is a delimiter open heredoc, else it is a syntax error 
 *		3. <
 *		4. >
*/
void ms_build_redirections(t_token *token,	t_process *process)
{
	t_err_key 	err_key;
	char 		*err_msg;
	pid_t		pid;
	
	err_key = ERROR_SYNTAX;
	err_msg = MSG_ERROR_SYNTAX_REDIRECT;
	if (token->type == TYPE_REDIRECT_DOUBLE_RIGHT || 
		token->type == TYPE_REDIRECT_RIGHT || 
		token->type == TYPE_REDIRECT_LEFT)
	{
		process->has_redirection = true;
		if (token->next && token->next->type == TYPE_ARG_REDIRECT_FILE)
			ms_add_redirection(process, token->type, ft_strdup(token->next->content));
		else
			ms_set_error(process->internal_error, err_key, err_msg);
	}
	else if	(token->type == TYPE_REDIRECT_DOUBLE_LEFT)
	{
		process->has_redirection = true;
		if (token->next && token->next->type == TYPE_ARG_DELIMITER)
		{
			pid = fork();
			if (pid == 0)
			{
				g_sig.in_heredoc = true;
				open_heredoc(token);
				g_sig.in_heredoc = false;	
				exit (0);
			}
			else
				g_sig.in_child = true;
			waitpid(pid, NULL, 0);	
			g_sig.in_child = false;		
			ms_add_redirection(process, token->type, ft_strdup(".heredoc"));
		}
		else
			ms_set_error(process->internal_error, err_key, err_msg);
	}
}
