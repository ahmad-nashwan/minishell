/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 01:42:29 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/27 02:50:01 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

void	exit_child(t_shell *shell, int exit_state)
{
	if (!shell)
		return;
	free_shell_state(shell);
	exit(exit_state);
}