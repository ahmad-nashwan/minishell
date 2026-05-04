# include "../../inc/minishell.h"

int	scan_redirection(t_shell *shell, t_string *line)
{
	if (peek(line) == '>')
	{
		advance(line);
		if (peek(line) == '>')
		{
			advance(line);
			add_token(&shell->tokens, NULL, APPEND);
		}
		else
			add_token(&shell->tokens,NULL, OUT_RED);
		return (0);
	}
	else if (peek(line) == '<')
	{
		advance(line); // consume <
		if (peek(line) == '<')
		{
			advance(line); // consume other <
			add_token(&shell->tokens, NULL, HEREDOC);
		}
		else
			add_token(&shell->tokens, NULL, IN_RED);
		return (0);
	}
	return (1);
}
