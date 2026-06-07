/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:19:54 by anashwan          #+#    #+#             */
/*   Updated: 2026/06/05 00:56:45 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_string	*get_var_name(t_string *line)
{
	t_string	*name;

	name = create_empty_string(32);
	if (!name)
		return (NULL);
	while (ft_isalnum(peek(line)) || peek(line) == '_')
	{
		if (append(name, advance(line)) != OK)
		{
			free_t_string(name);
			return (NULL);
		}
	}
	return (name);
}

t_code	expand_tilde(t_shell *shell, t_string *line, t_string *word)
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

t_code	expand_start(t_shell *shell, t_string *line, t_string *word, int quoted)
{
	char	c;

	advance(line);
	c = peek(line);
	if (c == '?')
		return (expand_exit_status(shell, line, word, quoted));
	if (!quoted && (c == '"' || c == '\''))
        return (OK);
	if (c == '0')
	{
		advance(line);
		return (append_str(word, "minishell"));
	}
	if (ft_isdigit(c))
	{
		advance(line);
		return (OK);
	}
	if (ft_isalpha(c) || c == '_')
		return (find_var_expand(shell, line, word, quoted));
	return (append(word, '$'));
}
