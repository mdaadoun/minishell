/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:12:25 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/17 14:34:54 by mdaadoun         ###   ########.fr       */
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
static void open_heredoc(t_minishell *ms, t_token *token, t_process *process)
{
	char	*line;
	char	*delimiter;
	int		check;

	delimiter = token->next->content;
	line = "";
	check = 1;
	while (check)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf("exit heredoc\n");
			break;
			// ms_set_error(ms->global_error, NO_ERROR, NULL);
			// exit(ms_free_before_exit(ms));
		}
		check = ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1);
		if (!check)
			break;
		add_heredoc_line(line);
		free(line);
	}
	free(process->redirected_filepath);
	process->redirected_filepath = strdup(".heredoc");
	ft_printf("read the last heredoc %s\n", process->redirected_filepath);
	(void) ms;
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
void ms_build_redirections(t_minishell *ms, t_token *token,	t_process *process)
{
	t_err_key 	err_key;
	char 		*err_msg;
	
	err_key = ERROR_SYNTAX;
	err_msg = MSG_ERROR_SYNTAX_REDIRECT;
	if (token->type == TYPE_REDIRECT_DOUBLE_RIGHT || 
		token->type == TYPE_REDIRECT_DOUBLE_LEFT || 
		token->type == TYPE_REDIRECT_LEFT || 
		token->type == TYPE_REDIRECT_RIGHT)
		{
			process->has_redirection = true;
			process->redirected_filepath = strdup("");
		}

	if (token->type == TYPE_REDIRECT_DOUBLE_RIGHT) 
		ft_printf("redirection double right.");

	else if	(token->type == TYPE_REDIRECT_DOUBLE_LEFT)
		if (token->next->type == TYPE_ARG_STRING)
			open_heredoc(ms, token, process);
		else
			ms_set_error(process->internal_error, err_key, err_msg);

	else if	(token->type == TYPE_REDIRECT_LEFT)
		ft_printf("redirection left");
	else if	(token->type == TYPE_REDIRECT_RIGHT)
		ft_printf("redirectoin right");
}