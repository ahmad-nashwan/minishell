/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_string.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:20:17 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/27 02:46:04 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	peek(t_string *line)
{
	if (line->index < line->len && line->str[line->index])
	{
		return (line->str[line->index]);
	}
	else
		return ('\0');
}

char	advance(t_string *line)
{
	if (line->index < line->len && line->str[line->index])
		return (line->str[line->index++]);
	return ('\0');
}

t_code	append(t_string *word, char c)
{
	if (word->len + 1 >= word->cap)
	{
		if (realloc_string(word) == INTERNAL_ERROR)
			return (INTERNAL_ERROR);
	}
	word->str[word->len++] = c;
	word->str[word->len] = '\0';
	return (OK);
}

void	free_t_string(t_string *str)
{
	if (!str)
		return ;
	if (str->str)
		free(str->str);
	free(str);
}
