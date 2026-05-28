/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:19:47 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:19:48 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_code	hdoc_expand_var(t_shell *shell, t_string *line, t_string *buff)
{
	t_string	*key;
	char		*value;

	key = get_var_name(line);
	if (!key)
	{
		report_error(shell, INTERNAL_ERROR, "Malloc failure");
		return (INTERNAL_ERROR);
	}
	value = get_env_value(shell->env_list, key->str);
	free_t_string(key);
	if (!value)
		return (OK); // expand nothing
	if (append_str(buff, value) != OK)
	{
		report_error(shell, INTERNAL_ERROR, "Malloc failure");
		return (INTERNAL_ERROR);
	}
	return (OK);
}

static t_code	hdoc_expand_exit(t_shell *shell, t_string *line, t_string *buff)
{
	char	*exit_status;

	advance(line);
	exit_status = ft_itoa(shell->exit_status);
	if (!exit_status)
		return (INTERNAL_ERROR);
	if (append_str(buff, exit_status) != OK)
	{
		free(exit_status);
		return (INTERNAL_ERROR);
	}
	free(exit_status);
	return (OK);
}

t_code	expand_hdoc(t_shell *shell, t_string *line, t_string *buff)
{
	char c;

	advance(line); // skip $
	c = peek(line);
	if (c == '?')
		return (hdoc_expand_exit(shell, line, buff));
	if (c == '0')
	{
		advance(line);
		return (append_str(buff, "minishell"));
	}
	if (ft_isdigit(c))
	{
		advance(line);
		return (OK);
	}
	if (ft_isalpha(c) || c == '_')
		return (hdoc_expand_var(shell, line, buff));
	return (append(buff, '$'));
}