/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:19:33 by anashwan          #+#    #+#             */
/*   Updated: 2026/06/07 14:57:53 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	advance(line);
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

static t_code   add_word_token(t_shell *shell, t_string *word, int q, int moved)
{
    if (word->len == 0 && !q)
    {
        if (moved)
            return (add_token(&shell->tokens, word->str, WORD, 0));
        return (NONE);
    }
    return (add_token(&shell->tokens, word->str, WORD, q));
}

t_code  scan_word(t_shell *shell, t_string *line)
{
    int         quoted;
    size_t      start;
    t_string    *word;
    t_code      rc;

    start = line->index;
    quoted = 0;
    word = create_empty_string(1024);
    if (!word)
        return (INTERNAL_ERROR);
    rc = normal_mode(shell, line, word, &quoted);
    if (rc == OK)
        rc = add_word_token(shell, word, quoted, line->index > start);
    if (rc != OK)
        free_t_string(word);
    else
        free(word);
    return (rc);
}
