/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:21:19 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:21:20 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_hdoc_strings(t_string *s1, t_string *s2)
{
	free_t_string(s1);
	free_t_string(s2);
}

static t_code	hdoc_process_line(t_shell *shell, char *input, int *fd,
		int quoted)
{
	t_string	*buff;
	t_string	*line;

	line = init_string(input);
	if (!line)
		return (ERR);
	buff = create_empty_string(1024);
	if (!buff)
	{
		free_t_string(line);
		return (ERR);
	}
	while (peek(line) != '\0')
	{
		if (hdoc_append_char(shell, line, buff, quoted) != OK)
		{
			free_hdoc_strings(line, buff);
			return (ERR);
		}
	}
	write(fd[1], buff->str, buff->len);
	write(fd[1], "\n", 1);
	free_hdoc_strings(line, buff);
	return (OK);
}

static t_code	hdoc_reader(t_shell *shell, char *delimeter, int quoted,
		int *fd)
{
	char	*line;
	t_code	rc;

	rc = NONE;
	while (rc == NONE)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = hdoc_read_line();
		if (g_signal)
			return (INTERRUPTED);
		if (!line)
		{
			hdoc_eof_error(delimeter);
			rc = OK;
			break ;
		}
		else if (ft_strcmp(line, delimeter) == 0)
			rc = OK;
		else if (hdoc_process_line(shell, line, fd, quoted) != OK)
			rc = ERR;
		free(line);
	}
	return (rc);
}

t_code	parse_hdoc(t_shell *shell, char *delimeter, int *h_fd, int quoted)
{
	int		fd[2];
	t_code	rc;

	if (pipe(fd) == -1)
	{
		report_error(shell, INTERNAL_ERROR, "Pipe failure");
		return (-1);
	}
	sig_set_heredoc();
	rc = hdoc_reader(shell, delimeter, quoted, fd);
	if (rc != OK)
	{
		if (rc == INTERRUPTED)
			shell->exit_status = 130;
		else if (rc == ERR)
			shell->exit_status = 1;
		close(fd[0]);
		close(fd[1]);
		sig_set_interactive();
		return (rc);
	}
	sig_set_interactive();
	close(fd[1]);
	*h_fd = fd[0];
	return (OK);
}
