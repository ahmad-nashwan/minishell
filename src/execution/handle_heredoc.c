# include "../../inc/minishell.h"

static  void    close_hdocs(t_list *redirections)
{
    t_redir *redir;

    if (!redirections)
        return ;
    while (redirections)
    {
        redir = (t_redir *)redirections->content;
        if (redir->type == HEREDOC)
        {
            if (redir->h_fd != -1)
                close(redir->h_fd);
        }
        redirections = redirections->next;
    }
}

void    close_hdoc_fds(t_list *cmds)
{
    t_cmd *c;
    if (!cmds)
        return ;
    while (cmds)
    {
        c = (t_cmd *) cmds->content;
        close_hdocs(c->redirections);
        cmds = cmds->next;
    }
}

t_code  handle_hdoc(t_redir *redir)
{
    if (redir->h_fd < 0)
        return (OK);
    if (dup2(redir->h_fd, STDIN_FILENO) == -1)
    {
        perror("minishell: dup2");
        close(redir->h_fd);
        return (ERR);
    }
    close(redir->h_fd);
    return (OK);
}
