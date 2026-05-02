# include "../../inc/minishell.h"



static void	quoted_mode(t_shell *shell, t_string *line, t_string *word)
{
	int		expand_flag;
	char	quote;

	expand_flag = 0;
	quote = line->str[line->index];
	if (quote == '"')
		expand_flag = 1;
	advance(line); // Opening quote
	while (line->index < line->len && line->str[line->index] != quote)
	{
		if (line->str[line->index] == '$' && expand_flag)
			expand(shell, line, word, 1);
		else
			append(word, advance(line));
	}
	if (line->index >= line->len)
		error_report(shell, "Invalid Quotes.", 1);
	advance(line); // Consume the closing quote
}

static void	normal_mode(t_shell *shell, t_string *line, t_string *word)
{
	char	c;

	while (line->index < line->len)
	{
		c = line->str[line->index];
		if(c == '|' || c == '<' || c == '>' || ft_isspace(c))
			break;
		if (c == '\'' || c == '"')
			quoted_mode(shell, line, word);
		else if (c == '$')
			expand(shell, line, word, 0);
		else 
			append(word, advance(line));
	}
}

int scan_word(t_shell *shell, t_string *line)
{
	t_string	*word;

	word = new_string(1024);
	if (!word)
		error_exit("Malloc Failure.");
	normal_mode(shell, line, word);
	if (word->len == 0)
	{
		free(word->str);
		free(word);
		return (0);
	}
	add_token(&shell->tokens, word->str, WORD);
	word->str = NULL;
	free(word);
	return (1);
}
