# include "../../inc/minishell.h"

static	void	append(t_string *word, char c)
{
	char	*ptr;

	if (word->len + 1 >= word->cap)
	{
		ptr = realloc_string(word);
		if (ptr == NULL)
		{
			free(word->str);
			free(word);
			error_exit("Malloc Failure");
		}
		word->str = ptr;
	}
	word->str[word->len++] = c;
	word->str[word->len] = '\0';
}

static void	quoted_mode(t_string *line, t_string *word)
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
			expand(line, word);
		else
			append(word, advance(line));
	}
	if (line->index >= line->len)
		error_exit("Invalid Quotes.");
	advance(line); // Consume the closing quote
}

static void	normal_mode(t_string *line, t_string *word)
{
	char	c;

	while (line->index < line->len)
	{
		c = line->str[line->index];
		if(c == '|' || c == '<' || c == '>')
			break;
		if (c == '\'' || c == '"')
			quoted_mode(line, word);
		else if (c == '$')
			expand(line, word);
		else 
			append(word, advance(line));
	}
}

int scan_word(t_token **tokens, t_string *line)
{
	t_string	*word;

	word = init_string(NULL);
	if (!word)
		error_report("Malloc Failure.");
	normal_mode(line, word);
	if (word->len == 0)
	{
		free(word->str);
		free(word);
		return (0);
	}
	add_token(tokens, word->str, WORD);
	word->str = NULL;
	free(word);
	return (1);
}
