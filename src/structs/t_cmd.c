/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:20:09 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:20:10 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*cmd_create(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv_list = NULL;
	cmd->redirections = NULL;
	return (cmd);
}

t_code	cmd_add_arg(t_cmd *cmd, char *lexeme)
{
	t_list	*node;
	char	*dup;

	if (!cmd || !lexeme)
		return (ERR);
	dup = ft_strdup(lexeme);
	if (!dup)
		return (INTERNAL_ERROR);
	node = ft_lstnew(dup);
	if (!node)
	{
		free(dup);
		return (INTERNAL_ERROR);
	}
	ft_lstadd_back(&cmd->argv_list, node);
	return (OK);
}

t_code	cmd_add_redir(t_cmd *cmd, t_redir *redir)
{
	t_list	*node;

	if (!cmd || !redir)
		return (ERR);
	node = ft_lstnew((void *)redir);
	if (!node)
		return (INTERNAL_ERROR);
	ft_lstadd_back(&cmd->redirections, node);
	return (OK);
}

void	cmd_free(void *p)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)p;
	if (!cmd)
		return ;
	if (cmd->argv_list)
		ft_lstclear(&cmd->argv_list, free);
	if (cmd->redirections)
		ft_lstclear(&cmd->redirections, redir_free);
	free(cmd);
}
