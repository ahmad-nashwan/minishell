# include "../../inc/minishell.h"

static t_code	token_error(t_shell *shell, t_code err)
{
	if (err == INTERNAL_ERROR)
		report_error(shell, err, "Internal error. Exitting.");
	else if (err == SYNTAX_ERROR)
		report_error(shell, err, "Unclosed quotes");
	return (err);
}

static t_code	try_scan_token(t_shell *shell, t_string *line)
{
	t_code	rc;

	rc = scan_word(shell, line);
	if (rc != NONE)
		return (rc);
	rc = scan_pipe(shell, line);
	if (rc != NONE)
		return (rc);
	rc = scan_redirection(shell, line);
	if (rc != NONE)
		return (rc);
	return (NONE);
}
t_code	tokenizer(t_shell *shell, t_string *line)
{
	t_code	rc;

	shell->tokens = NULL;
	while (line->index < line->len && line->str[line->index])
	{
		while (ft_isspace(line->str[line->index]))
			line->index++;
		rc = try_scan_token(shell, line);
		if (rc == INTERNAL_ERROR || rc == SYNTAX_ERROR)
			return token_error(shell, rc);
		if (rc == OK)
			continue;
	}
	if (add_token(&shell->tokens, NULL, END, 0) != OK)
		return token_error(shell, INTERNAL_ERROR);
	return OK;
}
