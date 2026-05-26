/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:19:56 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:19:57 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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
	t_string *name;
	char *value;
	t_code rc;

	name = get_var_name(line);
	if (!name)
		return (INTERNAL_ERROR);
	value = get_env_value(shell->env_list, name->str);
	free_t_string(name);
	if (!value)
		return (OK); // variable not found → append nothing
	rc = expand_var(shell, word, value, quoted);
	return (rc);
}