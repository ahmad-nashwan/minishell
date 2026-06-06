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

static void	clear_prev_hdoc(t_list *redirection)
{
	t_redir	*redir;

	if (!redirection)
		return ;
	while (redirection)
	{
		redir = (t_redir *)redirection->content;
		if (redir->h_fd != -1)
		{
			close(redir->h_fd);
			redir->h_fd = -1;
		}
		redirection = redirection->next;
	}
}

static t_code    parse_redir(t_shell *shell, t_cmd *cmd, t_token *redir,
        t_token *target)
{
    t_redir    *redirection;
    t_code    rc;

    if (!cmd || !redir || !target)
        return (INTERNAL_ERROR);
    redirection = redir_create(redir->type, target->lexeme);
    if (!redirection)
        return (INTERNAL_ERROR);
    if (redirection->type == HEREDOC)
    {
        clear_prev_hdoc(cmd->redirections);
        rc = parse_hdoc(shell, redirection->target, &redirection->h_fd,
                target->quoted);
        if (rc != OK)
        {
            free(redirection->target);
            free(redirection);
            return (rc);
        }
    }
    return (cmd_add_redir(cmd, redirection));
}

static t_code	handle_redir_node(t_shell *shell, t_cmd *cmd, t_list **node,
		t_token *token)
{
	t_token	*next_token;
	t_code	rc;

	if (!(*node)->next)
		return (report_syntax_error("newline"));
	next_token = (t_token *)(*node)->next->content;
	if (next_token->type != WORD)
		return (report_syntax_error(next_token->lexeme));
	rc = parse_redir(shell, cmd, token, next_token);
	if (rc != OK)
		return (rc);
	(*node) = (*node)->next->next;
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
			if (cmd_add_arg(cmd, token->lexeme) != OK)
				return (INTERNAL_ERROR);
			(*node) = (*node)->next;
		}
	}
	return (OK);
}