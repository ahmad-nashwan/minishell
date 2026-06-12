/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:20:14 by anashwan          #+#    #+#             */
/*   Updated: 2026/06/07 10:55:47 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*redir_create(t_type type, char *target)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->h_fd = -1;
	redir->target = ft_strdup(target);
	if (!redir->target)
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

void	redir_free(void *p)
{
	t_redir	*redir;

	redir = (t_redir *)p;
	if (!redir)
		return ;
	if (redir->h_fd != -1)
		close(redir->h_fd);
	if (redir->target)
		free(redir->target);
	free(redir);
}

int	is_hdoc_target(t_list *tokens)
{
	t_list	*last;
	t_token	*t;

	if (!tokens)
		return (0);
	last = ft_lstlast(tokens);
	t = (t_token *)last->content;
	if (t->type == HEREDOC)
		return (1);
	return (0);
}
