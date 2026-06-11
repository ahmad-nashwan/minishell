/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hdoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:21:16 by anashwan          #+#    #+#             */
/*   Updated: 2026/06/10 14:31:07 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hdoc_eof_error(char *delimeter)
{
	ft_putstr_fd("\nminishell: warning: here-document at line 0",
		STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimeter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

t_code	hdoc_append_char(t_shell *shell, t_string *line, t_string *buff,
		int quoted)
{
	if (peek(line) == '$' && !quoted)
	{
		expand_hdoc(shell, line, buff);
		return (OK);
	}
	return (append(buff, advance(line)));
}

static t_code	fill_hdoc_buffer(t_string *buf, int *bytes)
{
	char	c;

	while (1)
	{
		*bytes = read(STDIN_FILENO, &c, 1);
		if (*bytes == -1 && g_signal == 130)
			return (ERR);
		if (*bytes == -1)
			continue ;
		if (*bytes == 0 || c == '\n')
			break ;
		if (append(buf, c) != OK)
			return (ERR);
	}
	return (OK);
}

char	*hdoc_read_line(void)
{
	t_string	*buf;
	char		*res;
	int			bytes;

	buf = create_empty_string(1024);
	if (!buf)
		return (NULL);
	if (fill_hdoc_buffer(buf, &bytes) == ERR || (buf->len == 0 && bytes == 0))
	{
		free_t_string(buf);
		return (NULL);
	}
	res = buf->str;
	free(buf);
	return (res);
}
