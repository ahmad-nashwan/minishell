# include "../../inc/minishell.h"

int	scan_pipe(t_list **tokens, t_string *line)
{
	if (peek(line) == '|')
	{
		advance(line);
		add_token(tokens, NULL, PIPE);
		return (1);
	}
	return (0);
}
