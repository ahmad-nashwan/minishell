/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:19:24 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:19:25 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_code	scan_pipe(t_shell *shell, t_string *line)
{
	if (peek(line) == '|')
	{
		advance(line);
		if (add_token(&shell->tokens, NULL, PIPE, 0) != OK)
			return (INTERNAL_ERROR);
		return (OK);
	}
	return (NONE);
}
