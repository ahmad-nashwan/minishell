# include "../../inc/minishell.h"

int	scan_pipe(t_shell *shell, t_string *line)
{
	if (peek(line) == '|')
	{
		advance(line);
		add_token(&shell->tokens, NULL, PIPE);
		return (0);
	}
	return (1);
}
