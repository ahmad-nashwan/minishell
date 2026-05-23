# include "../../inc/minishell.h"

static t_code error(t_shell *shell, t_code e, char *msg)
{
    report_error(shell, e, msg);
    return (ERR);
}

static t_code process_cmd(t_shell *shell, t_list *node, int *input_fd, pid_t *pid)
{
    int fd[2];
    t_cmd *cmd;

    cmd = (t_cmd *)node->content;
    if (node->next && pipe(fd) != 0)
        return (error(shell, INTERNAL_ERROR, "Pipe failure"));
    *pid = fork();
    if (*pid == -1)
        return (error(shell, INTERNAL_ERROR, "Fork failed"));
    if (*pid == 0)
    {
        if (node->next)
            run_child(shell, cmd, *input_fd, fd);
        else
            run_child(shell, cmd, *input_fd, NULL);
        exit(shell->exit_status);
    }
    if (*input_fd != -1)
        close(*input_fd);
    if (node->next)
    {
        close(fd[1]);
        *input_fd = fd[0]; 
    }
    return (OK);
}

static void wait_for_children(t_shell *shell, pid_t *pids, int len)
{
    int i;
    int state;
    
    i = 0;
    while (i < len)
    {
        waitpid(pids[i], &state, 0);
        if (i == len - 1)
        {
            if (WIFEXITED(state))
                shell->exit_status = WEXITSTATUS(state);
            else if (WIFSIGNALED(state))
                shell->exit_status = 128 + WTERMSIG(state);
        }
        i++;
    }
}

t_code process_pipeline(t_shell *shell)
{
    t_list  *node;
    pid_t   *pids;
    int     i;
    int     input_fd;

    pids = malloc(sizeof(pid_t) * ft_lstsize(shell->cmds));
    if (!pids)
        return (error(shell, INTERNAL_ERROR, "Malloc failed"));
    i = 0;
    input_fd = -1;
    node = shell->cmds;
    while (!shell->should_exit && node)
    {
        if (process_cmd(shell, node, &input_fd, &pids[i]) != OK)
            break ;
        node = node->next;
        i++;
    }
    wait_for_children(shell, pids, i);
    free(pids);
    return (OK);
}
