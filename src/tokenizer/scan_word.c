#include "../../inc/minishell.h"

static t_code	expand_tilde(t_shell *shell, t_string *line, t_string *word)
{
	char	*home;
	char	next;

	advance(line);
	next = peek(line);
	if (next != '/' && next != '\0' && !ft_isspace(next))
		return (append(word, '~'));
	home = get_env_value(shell->env_list, "HOME");
	if (home)
		return (append_str(word, home));
	return (append(word, '~'));
}

static t_code	quoted_mode(t_shell *shell, t_string *line, t_string *word,
		int hdoc_target)
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
		if (line->str[line->index] == '$' && expand_flag && !hdoc_target)
		{
			if (expand_start(shell, line, word, 1) != OK)
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
	return (OK);
}

static t_code	normal_mode(t_shell *shell, t_string *line, t_string *word,
		int *quoted)
{
	char	c;
	t_code	result;
	int		hdoc_target;

	result = OK;
	hdoc_target = is_hdoc_target(shell->tokens);
	while (line->index < line->len)
	{
		c = line->str[line->index];
		if (result != OK || c == '|' || c == '<' || c == '>' || ft_isspace(c))
			break ;
		if (c == '\'' || c == '"')
		{
			*quoted = 1;
			result = quoted_mode(shell, line, word, hdoc_target);
		}
		else if (c == '$' && !hdoc_target)
			result = expand_start(shell, line, word, 0);
		else if (c == '~' && word->len == 0 && !hdoc_target)
			result = expand_tilde(shell, line, word);
		else
			result = append(word, advance(line));
	}
	return (result);
}

t_code	scan_word(t_shell *shell, t_string *line)
{
	t_string	*word;
	int			quoted;
	t_code		rc;

	quoted = 0;
	word = create_empty_string(1024);
	if (!word)
		return (INTERNAL_ERROR);
	rc = normal_mode(shell, line, word, &quoted);
	if (rc == OK && word->len == 0 && !quoted)
		rc = NONE;
	else if (rc == OK && add_token(&shell->tokens, word->str, WORD,
			quoted) != OK)
		rc = INTERNAL_ERROR;
	if (rc != OK)
	{
		free_t_string(word);
		return (rc);
	}
	word->str = NULL;
	free(word);
	return (OK);
}
