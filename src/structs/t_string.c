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

t_string	*init_string(char *str)
{
	t_string	*string;

	if (!str)
		return (NULL);
	string = malloc(sizeof(t_string));
	if (!string)
		return (NULL);
	string->index = 0;
	string->str = ft_strdup(str);
	if (!string->str)
	{
		free(string);
		return (NULL);
	}
	string->len = ft_strlen(str);
	string->cap = string->len + 1;
	return (string);
}

t_string	*create_empty_string(size_t cap)
{
	t_string	*string;

	if (cap <= 0)
		cap = 16;
	string = malloc(sizeof(t_string));
	if (!string)
		return (NULL);
	string->index = 0;
	string->len = 0;
	string->cap = cap;
	string->str = malloc(cap);
	if (!string->str)
	{
		free(string);
		return (NULL);
	}
	string->str[0] = '\0';
	return (string);
}

t_code	realloc_string(t_string *word)
{
	size_t	new_cap;
	char	*new_str;
	size_t	i;

	if (word->cap == 0)
		new_cap = 16;
	else
		new_cap = word->cap * 2;
	new_str = malloc(new_cap);
	if (!new_str)
		return (INTERNAL_ERROR);
	i = 0;
	while (i < word->len)
	{
		new_str[i] = word->str[i];
		i++;
	}
	new_str[i] = '\0';
	free(word->str);
	word->str = new_str;
	word->cap = new_cap;
	return (OK);
}

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