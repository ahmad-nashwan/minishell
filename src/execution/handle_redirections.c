# include "../../inc/minishell.h"

static int  get_fd(t_redir *redir)
{
    int fd;

    fd = -1;
    if (redir->type == IN_RED) // <
        fd = open(redir->target, O_RDONLY);
    else if (redir->type == OUT_RED) // >
        fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (redir->type == APPEND) // >>
        fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        perror(redir->target);
    }
    return (fd);
}

static t_code safe_redirection(t_redir *redir, int fd)
{
    int rc;
    if (redir->type == IN_RED)
        rc = dup2(fd, STDIN_FILENO);
    else
        rc = dup2(fd, STDOUT_FILENO);
    if (rc == -1)
        return (ERR);
    return (OK);
}

t_code  handle_redirections(t_cmd *cmd)
{
    t_redir *redir;
    t_list  *node;
    int     fd;

    node = cmd->redirections;
    while (node)
    {
        redir = (t_redir *)node->content;
        fd = get_fd(redir);
        if (fd == -1)
            return (ERR);
        if (safe_redirection(redir, fd) == ERR)
        {
            perror("minishell: dup2");
            close(fd);
            return (ERR);
        }
        close(fd);
        node = node->next;
    }
    return (OK);
}
