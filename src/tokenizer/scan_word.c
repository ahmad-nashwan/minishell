# include "../../inc/minishell.h"

static int	quoted_mode(t_shell *shell, t_string *line, t_string *word)
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
	if (line->index >= line->len) // unclosed quotes
		return (1);
	advance(line); // Consume the closing quote
	return (0); // everything is ok
}

static int	normal_mode(t_shell *shell, t_string *line, t_string *word, int *quoted)
{
	char	c;

	while (line->index < line->len)
	{
		c = line->str[line->index];
		if(c == '|' || c == '<' || c == '>' || ft_isspace(c))
			break;
		if (c == '\'' || c == '"')
		{
			*quoted = 1;
			if (quoted_mode(shell, line, word))
				return (1); // take error upwards to the responsible function
		}
		else if (c == '$')
		{
			expand(shell, line, word, 0);
		}
		else
		{ 
			append(word, advance(line));
		}
	}
	return (0);
}

int scan_word(t_shell *shell, t_string *line)
{
	t_string	*word;
	int			quoted;

	quoted = 0;
	word = new_string(1024);
	if (!word)
		error_exit("Malloc Failure.");
	if (normal_mode(shell, line, word, &quoted))
		return (-1);
	if (word->len == 0 && !quoted)
	{
		free(word->str);
		free(word);
		return (1);
	}
	add_token(&shell->tokens, word->str, WORD);
	word->str = NULL;
	free(word);
	return (0);
}
