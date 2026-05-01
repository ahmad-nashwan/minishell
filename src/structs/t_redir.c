# include "../../inc/minishell.h"

t_redir *redir_create(t_type type, char *target)
{
    t_redir *redir;

    redir = malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    redir->type = type;
    redir->target = ft_strdup(target);
    if (!redir->target)
    {
        free(redir);
        return (NULL);
    }
    return (redir);
}

void    redir_free(t_redir *redir)
{
    if (!redir)
        return ;
    if (redir->target)
        free(redir->target);
    free(redir);
}