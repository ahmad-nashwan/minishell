# include "../../inc/minishell.h"

void run_child(t_shell *shell, t_cmd *cmd, int input_fd, int *pipe_fd)
{
    // 1. Hook up pipes
    if (input_fd != -1)
    {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    if (pipe_fd != NULL)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
    }

    // 2. Hook up redirections 
    if (handle_redirections(shell, cmd) != OK)
        exit(1);

    // 3. Reset signals so the child can be killed normally!
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);

    // 4. Execute the command
    // execute_command(shell, cmd);
    
    exit(shell->exit_status);
}
