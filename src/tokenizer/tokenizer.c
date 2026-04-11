# include "../../inc/minishell.h"

int tokenizer(t_shell *shell, t_string *line)
{
	shell->tokens = NULL;
	while (line->index < line->len && line->str[line->index])
	{
		while(ft_isspace(line->str[line->index]))
			line->index++;
		if (scan_word(shell, line))
			continue;
		else if (scan_pipe(shell, line))
			continue;
		else if (scan_redirection(shell, line))
			continue;
	}
	add_token(&shell->tokens, NULL, END);
	return (0);
}
