/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:19:56 by anashwan          #+#    #+#             */
/*   Updated: 2026/06/07 14:58:43 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_code	expand_var(t_shell *shell, t_string *word, char *value, int quoted)
{
	if (!quoted && ft_strchr(value, ' '))
		return (expand_split(word, shell, value));
	else
		return (append_str(word, value));
}

t_code	find_var_expand(t_shell *shell, t_string *line, t_string *word,
		int quoted)
{
	char		*value;
	t_code		rc;
	t_string	*name;

	name = get_var_name(line);
	if (!name)
		return (INTERNAL_ERROR);
	value = get_env_value(shell->env_list, name->str);
	free_t_string(name);
	if (!value)
		return (OK);
	rc = expand_var(shell, word, value, quoted);
	return (rc);
}
