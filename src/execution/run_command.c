# include "../../inc/minishell.h"

static void exec_absolute_path(char **argv, char **envp)
{
    // file doesn't exist
    if (access(argv[0], F_OK) == -1)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        perror(argv[0]);
        exit(127);
    }
    // file exists but something is wrong, ex: permission or its a dir
    if (access(argv[0], X_OK) == -1)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        perror(argv[0]);
        exit(126);
    }
    // if it fails, print the error, if it works, the following lines are never reached since they are wiped from ram
    execve(argv[0], argv, envp);
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    perror(argv[0]);
    exit(126);
}

static void print_err_exit(char *cmd, char *msg, int code)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(cmd, STDERR_FILENO);
    ft_putstr_fd(msg, STDERR_FILENO);
    exit(code);
}

static void search_and_exec(t_shell *shell, char **argv, char **envp)
{
    char    *path_env;
    char    **paths;
    char    *path;

    path_env = get_env_val(shell->env_list, "PATH");
    if (!path_env)
        print_err_exit(argv[0], ": No such file or directory\n", 127);
    paths = ft_split(path_env, ':');
    if (!paths)
        exit(1);
        
    path = get_valid_path(paths, argv[0]);
    free_split(paths); 
    if (path)
    {
        execve(path, argv, envp);
        perror("minishell");
        free(path);
        exit(126);
    }
    print_err_exit(argv[0], ": command not found\n", 127);
}

void execute_command(t_shell *shell, t_cmd *cmd)
{
    char **argv;
    char **envp;   

    if (run_builtin(shell, cmd) == OK)
        exit(shell->exit_status);
    argv = list_to_array(cmd->argv_list);
    if (!argv)
        exit(1);
    envp = get_env_array(shell->env_list); // THIS ONE CAN BE NULL
    if (ft_strchr(argv[0], '/'))
        exec_absolute_path(argv, envp);
    else
        search_and_exec(shell, argv, envp);
    
    free_strings_array(argv, ft_lstsize(cmd->argv_list));
    free_strings_array(envp, ft_lstsize(shell->env_list));
    // If we reach here, execve failed or command wasn't found.
    // The path functions should print the error and exit(127) or exit(126).
}

void run_child(t_shell *shell, t_cmd *cmd, int input_fd, int *pipe_fd)
{
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
    if (handle_redirections(shell, cmd) != OK)
        exit(1);
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    execute_command(shell, cmd);
    exit(shell->exit_status);
}
