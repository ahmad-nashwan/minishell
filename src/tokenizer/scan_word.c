# include "../../inc/minishell.h"

static t_code quoted_mode(t_shell *shell, t_string *line, t_string *word)
{
	int		expand_flag;
	char	quote;

	expand_flag = 0;
	quote = line->str[line->index];
	if (quote == '"')
		expand_flag = 1;
	advance(line);
	while (line->index < line->len && line->str[line->index] != quote)
	{
		if (line->str[line->index] == '$' && expand_flag)
		{
			if (init_expand(shell, line, word, 1) != OK) 
				return (INTERNAL_ERROR);
		}
		else
		{
			if (append(word, advance(line)) != OK)
				return (INTERNAL_ERROR);
		}
	}
	if (line->index >= line->len)
		return (SYNTAX_ERROR);
	advance(line); // closing quote
	return OK;
}

static t_code	normal_mode(t_shell *shell, t_string *line, t_string *word, int *quoted)
{
	char	c;
	t_code	result;

	result = OK;
	while (line->index < line->len)
	{
		c = line->str[line->index];
		if(result != OK || c == '|' || c == '<' || c == '>' || ft_isspace(c))
			break;
		if (c == '\'' || c == '"')
		{
			*quoted = 1;
			result = quoted_mode(shell, line, word);
		}
		else if (c == '$')
		{
			result = init_expand(shell, line, word, 0);
		}
		else
		{
			if (append(word, advance(line)) == INTERNAL_ERROR)
				return (INTERNAL_ERROR); 
		}
	}
	return (result);
}

t_code scan_word(t_shell *shell, t_string *line)
{
	t_string	*word;
	int			quoted;
	t_code		rc;

	quoted = 0;
	word = new_string(1024);
	if (!word)
		return INTERNAL_ERROR;
	rc = normal_mode(shell, line, word, &quoted);
	if (rc != OK)
	{
		free_t_string(word);
		return (rc);
	}
	else if (word->len == 0 && !quoted)
	{
		free_t_string(word);
		return (NONE);
	}
	else if (add_token(&shell->tokens, word->str, WORD) != OK)
	{
		printf("SUP\n");
		free_t_string(word);
		return (INTERNAL_ERROR);
	}
	word->str = NULL;
	free(word);
	return (OK);
}
