# include "../../inc/minishell.h"

int tokenizer(t_shell *shell, t_string *line)
{
	shell->tokens = NULL;
	int	result;
	while (line->index < line->len && line->str[line->index])
	{
		while(ft_isspace(line->str[line->index]))
			line->index++;
		result = scan_word(shell, line);
		if (result == -1)
		{
			report_error(shell, ERR_SYNTAX, "Unclosed quotes");
			return (1);
		}
		if (result == 0)
			continue;
		result = scan_pipe(shell, line);
		if (result == 0)
			continue;
		result = scan_redirection(shell, line);
		if (result == 0)
			continue;
	}
	add_token(&shell->tokens, NULL, END);
	return (0);
}
