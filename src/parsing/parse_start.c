/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:21:22 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:21:23 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_code	consume_pipe(t_list **node)
{
	t_token	*token;
	t_token	*next_token;
	t_list	*n;

	n = (*node);
	token = (t_token *)n->content;
	if (token->type == END)
		return (OK);         // Do nothing
	if (token->type == PIPE) // real work
	{
		if (!n->next)
			return (report_syntax_error("|")); // Syntax error, pipe at the end
		next_token = (t_token *)n->next->content;
		if (next_token->type == END || next_token->type == PIPE)
			return (report_syntax_error("|")); // Syntax error
		(*node) = (*node)->next;               // consume pipe
	}
	return (OK);
}

static t_code	process_node(t_shell *shell, t_list **node)
{
	t_cmd	*cmd;
	t_token	*token;
	t_code	rc;

	token = (t_token *)(*node)->content;
	if (token->type == PIPE)
	{
		report_syntax_error("|");
		return (parse_error(shell, NULL, &shell->cmds, SYNTAX_ERROR));
	}
	cmd = cmd_create();
	if (!cmd)
		return (parse_error(shell, NULL, &shell->cmds, INTERNAL_ERROR));
	rc = build_cmd(shell, cmd, node);
	if (rc != OK)
		return (parse_error(shell, cmd, &shell->cmds, rc));
	rc = consume_pipe(node);
	if (rc != OK)
		return (parse_error(shell, cmd, &shell->cmds, rc));
	rc = cmd_list_add(&shell->cmds, cmd);
	if (rc != OK)
		return (parse_error(shell, cmd, &shell->cmds, rc));
	return (OK);
}

t_code	parse(t_shell *shell)
{
	t_list	*node;
	t_token	*token;
	t_code	rc;

	node = shell->tokens;
	while (!shell->should_exit && node)
	{
		token = (t_token *)node->content;
		if (token->type == END)
			break ;
		rc = process_node(shell, &node);
		if (rc != OK)
			return (rc);
	}
	return (OK);
}
