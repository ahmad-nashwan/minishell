/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:21:19 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:21:20 by anashwan         ###   ########.fr       */
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

static t_code	setup_heredoc(t_shell *shell, t_cmd *cmd, t_redir *redir,
		int quoted)
{
	t_code	rc;

	clear_prev_hdoc(cmd->redirections);
	rc = parse_hdoc(shell, redir->target, &redir->h_fd, quoted);
	return (rc);
}

t_code	parse_redir(t_shell *shell, t_cmd *cmd, t_token *redir, t_token *target)
{
	t_redir	*redirection;
	t_code	rc;

	if (!cmd || !redir || !target || !target->lexeme)
		return (INTERNAL_ERROR);
	if (target->lexeme[0] == '\0' && !target->quoted)
		redir->type = AMBIG_REDIR;
	redirection = redir_create(redir->type, target->lexeme);
	if (!redirection)
		return (INTERNAL_ERROR);
	if (redirection->type == HEREDOC)
	{
		rc = setup_heredoc(shell, cmd, redirection, target->quoted);
		if (rc != OK)
		{
			redir_free(redirection);
			return (rc);
		}
	}
	rc = cmd_add_redir(cmd, redirection);
	if (rc != OK)
		redir_free(redirection);
	return (rc);
}

t_code	handle_redir_node(t_shell *shell, t_cmd *cmd, t_list **node,
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
