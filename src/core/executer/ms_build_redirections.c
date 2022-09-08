/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_build_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:12:25 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/09/08 08:13:34 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	add_heredoc_line(char *line, bool nl)
{
	int	fd;

	fd = open(".heredoc", O_CREAT | O_WRONLY | O_APPEND, 0777);
	write(fd, line, ft_strlen(line));
	if (nl)
		write(fd, "\n", 1);
	close(fd);
}

/*
 *	The heredoc loop:
 *		get the delimiter, and wait for the delimiter
 *		each line are added to a temporary file .heredoc
 */
static void	open_heredoc(void)
{
	char	*line;
	int		check;
	size_t	len;

	line = "";
	check = 1;
	unlink(".heredoc");
	add_heredoc_line(line, false);
	while (check)
	{
		line = readline("> ");
		if (!line)
			break ;
		len = ft_strlen(g_sig.delimiter) + 1;
		check = ft_strncmp(line, g_sig.delimiter, len);
		if (!check)
		{
			free(line);
			break ;
		}
		add_heredoc_line(line, true);
		free(line);
	}
}

static void	child_heredoc(t_minishell *ms, t_token *token)
{
	g_sig.in_heredoc = true;
	g_sig.delimiter = ft_strdup(token->next->content);
	ms_free_last_command(ms);
	ms_free_before_exit(ms);
	open_heredoc();
	g_sig.in_heredoc = false;
	free(g_sig.delimiter);
	exit (0);
}

static void	run_heredoc(t_minishell *ms, t_token *token, t_process *proc)
{
	pid_t		pid;

	proc->has_redirection = true;
	if (token->next && token->next->type == TYPE_ARG_DELIMITER)
	{
		g_sig.exit_status = 0;
		pid = fork();
		if (pid == 0)
			child_heredoc(ms, token);
		g_sig.in_child = true;
		waitpid(pid, NULL, 0);
		g_sig.in_child = false;
		ms_add_redir(proc, token->type, ft_strdup(".heredoc"));
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
void	ms_build_redir(t_minishell *ms, t_token *token,	t_process *process)
{
	t_err_key	err_key;
	char		*err_msg;

	err_key = ERROR_SYNTAX;
	err_msg = MSG_ERROR_SYNTAX_REDIRECT;
	if (is_redirect(token) > 1)
	{
		process->has_redirection = true;
		if (token->next && token->next->type == TYPE_ARG_REDIRECT_FILE)
			ms_add_redir(process, token->type, ft_strdup(token->next->content));
		else
			ms_set_error(ms->global_error, err_key, err_msg);
	}
	else if (token->type == TYPE_REDIRECT_DOUBLE_LEFT)
	{
		process->has_redirection = true;
		if (token->next && token->next->type == TYPE_ARG_DELIMITER)
			run_heredoc(ms, token, process);
		else
			ms_set_error(ms->global_error, err_key, err_msg);
	}
}
