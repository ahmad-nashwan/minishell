/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 20:56:25 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 20:56:46 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_child_pids(t_shell *shell)
{
   if (shell->child_pids)
        free(shell->child_pids);
    shell->child_pids = NULL;
}

void init_child_pids(t_shell *shell)
{
    shell->child_pids = malloc(sizeof(pid_t) * (ft_lstsize(shell->cmds) + 1));
    if (!shell->child_pids)
        error_exit("Malloc failure.");
}
