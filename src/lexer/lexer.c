# include "../../inc/minishell.h"

t_list	*start_lexer(t_string *line)
{
	token_type type;
	int		start;
	t_list 	*tokens;
	char	*word;

	tokens = NULL;
	while (line->index < line->len && line->str[line->index])
	{
		while(ft_isspace(line->str[line->index]))
			line->index++;
		start = line->index;
		if (scan_word(&tokens, line));
		else if (scan_pipe(&tokens, line));
		else if (scan_redirection(&tokens, line));
	}
	return (tokens);
}
