#include "../../inc/minishell.h"

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
	if (redir->target)
		free(redir->target);
	free(redir);
}

int	is_hdoc_target(t_list *tokens)
{
	t_token *t;
	t_list *last;

	if (!tokens)
		return (0); // empty list
	last = ft_lstlast(tokens);
	t = (t_token *)last->content;
	if (t->type == HEREDOC)
		return (1);
	return (0);
}