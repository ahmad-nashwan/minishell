/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_build_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:21:09 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:21:10 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_code add_argument_helper(t_cmd *cmd, t_token *token)
{
	if (!cmd || !token || !token->lexeme)
		return (INTERNAL_ERROR);
	if (token->lexeme[0] == '\0' && !token->quoted)
		return (OK);
	if (cmd_add_arg(cmd, token->lexeme) != OK)
		return (INTERNAL_ERROR);
	return (OK);
}

t_code	build_cmd(t_shell *shell, t_cmd *cmd, t_list **node)
{
	t_token *token;
	t_code rc;

	while (!shell->should_exit && *node)
	{
		token = (t_token *)(*node)->content;
		if (token->type == PIPE || token->type == END)
			return (OK);
		if (token->type != WORD)
		{
			rc = handle_redir_node(shell, cmd, node, token);
			if (rc != OK)
				return (rc);
		}
		else
		{
			rc = add_argument_helper(cmd, token);
			if (rc != OK)
				return (rc);
			(*node) = (*node)->next;
		}
	}
	return (OK);
}
