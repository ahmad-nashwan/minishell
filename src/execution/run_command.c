# include "../../inc/minishell.h"

static void exec_absolute_path(char **argv, char **envp)
{
    // file doesn't exist
    if (argv[0] && is_dir(argv[0]) == OK)
        free_argv_envp_exit(argv, envp, 126);
    if (access(argv[0], F_OK) == -1)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        perror(argv[0]);
            free_argv_envp_exit(argv, envp, 127);
    }
    // file exists but something is wrong, ex: permission or its a dir
    if (access(argv[0], X_OK) == -1)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        perror(argv[0]);
        free_argv_envp_exit(argv, envp, 126);
    }
    // if it fails, print the error, if it works, the following lines are never reached since they are wiped from ram
    execve(argv[0], argv, envp);
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    perror(argv[0]);
    free_argv_envp_exit(argv, envp, 126);
}

static void execute_valid_path(char *path, char **argv, char **envp)
{
    if (is_dir(path) == OK)
    {
        free(path);
        free_argv_envp_exit(argv, envp, 126);
    }
    execve(path, argv, envp);
    perror("minishell");
    free(path);
    free_argv_envp_exit(argv, envp, 126);
}

static void search_and_exec(t_shell *shell, char **argv, char **envp)
{
    char    *path_env;
    char    **paths;
    char    *path;

    path_env = get_env_value(shell->env_list, "PATH");
    if (!path_env)
    {
        print_cmd_error(argv[0], ": No such file or directory\n");
        free_argv_envp_exit(argv, envp, 127);
    }
    paths = ft_split(path_env, ':');
    if (!paths)
        free_argv_envp_exit(argv, envp, 1);
    path = get_valid_path(paths, argv[0]);
    free_split(paths); 
    if (path && is_dir(path) == OK)
    {
        free(path);
        free_argv_envp_exit(argv, envp, 126);
    }
    if (path)
        execute_valid_path(path, argv, envp);
    print_cmd_error(argv[0], ": command not found\n");
    free_argv_envp_exit(argv, envp, 127);
}

void execute_command(t_shell *shell, t_cmd *cmd)
{
    char **argv;
    char **envp;   

    if (run_builtin(shell, cmd) == OK)
        exit(shell->exit_status);
        
    argv = list_to_string_array(cmd->argv_list);
    if (!argv)
        exit(1);
    if (!argv[0])
        free_argv_envp_exit(argv, NULL, 0);
    envp = get_env_array(shell->env_list);
    if (!envp)
        free_argv_envp_exit(argv, NULL, 1);
    if (ft_strchr(argv[0], '/'))
        exec_absolute_path(argv, envp);
    else
        search_and_exec(shell, argv, envp);
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
    if (handle_redirections(cmd) != OK)
        exit(1);
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    execute_command(shell, cmd);
    exit(shell->exit_status);
}
