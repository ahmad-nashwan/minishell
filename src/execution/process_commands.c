/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:40:29 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:40:30 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	is_builtin(char *name)
{
	if (ft_strncmp(name, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(name, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(name, "export", 7) == 0)
		return (1);
	if (ft_strncmp(name, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(name, "env", 4) == 0)
		return (1);
	if (ft_strncmp(name, "exit", 5) == 0)
		return (1);
	return (0);
}

t_code	process_commands(t_shell *shell)
{
	t_cmd	*cmd;

	if (ft_lstsize(shell->cmds) == 1)
	{
		cmd = (t_cmd *)shell->cmds->content;
		if (cmd->argv_list && is_builtin((char *)cmd->argv_list->content))
			return (process_single_builtin(shell, cmd));
	}
	return (process_pipeline(shell));
}
