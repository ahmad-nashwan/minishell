# include "../../inc/minishell.h"

t_code	scan_pipe(t_shell *shell, t_string *line)
{
	if (peek(line) == '|')
	{
		advance(line);
		if (add_token(&shell->tokens, NULL, PIPE, 0) != OK)
			return (INTERNAL_ERROR);
		return (OK);
	}
	return (NONE);
}
