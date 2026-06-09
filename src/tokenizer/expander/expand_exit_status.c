/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:19:44 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:19:45 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_code	expand_exit_status(t_shell *shell, t_string *line, t_string *word,
		int quoted)
{
	char	*value;
	t_code	rc;

	advance(line);
	value = ft_itoa(shell->exit_status);
	if (!value)
		return (INTERNAL_ERROR);
	rc = expand_var(shell, word, value, quoted);
	free(value);
	return (rc);
}
