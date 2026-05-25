# include "../../inc/minishell.h"

static t_code	scan_append_redir(t_shell *shell, t_string *line)
{
	advance(line); // consume first '>'

	if (peek(line) == '>')
	{
		advance(line);
		if (add_token(&shell->tokens, NULL, APPEND, 0) != OK)
			return (INTERNAL_ERROR);
	}
	else
	{
		if (add_token(&shell->tokens, NULL, OUT_RED, 0) != OK)
			return (INTERNAL_ERROR);
	}
	return (OK);
}

static t_code	scan_input_redir(t_shell *shell, t_string *line)
{
	advance(line); // consume '<'

	if (peek(line) == '<')
	{
		advance(line);
		if (add_token(&shell->tokens, NULL, HEREDOC, 0) != OK)
			return (INTERNAL_ERROR);
	}
	else
	{
		if (add_token(&shell->tokens, NULL, IN_RED, 0) != OK)
			return (INTERNAL_ERROR);
	}
	return (OK);
}

t_code	scan_redirection(t_shell *shell, t_string *line)
{
	char c;

	c = peek(line);

	if (c == '>')
		return (scan_append_redir(shell, line));
	else if (c == '<')
		return (scan_input_redir(shell, line));

	return (NONE);
}
