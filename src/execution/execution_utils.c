# include "../../inc/minishell.h"

char    *get_valid_path(char **paths, char *cmd)
{
    char    *temp;
    char    *full_path;
    int     i;

    i = 0;
    while (paths && paths[i])
    {
        temp = ft_strjoin(paths[i], "/");
        if (!temp)
            return (NULL);
        full_path = ft_strjoin(temp, cmd);
        free(temp);
        if (!full_path)
            return (NULL);
        if (access(full_path, X_OK) == 0)
            return (full_path);
        free(full_path);
        i++;
    }
    return (NULL);
}

t_code  is_dir(char *path)
{
    struct stat path_stat;

    if (stat(path, &path_stat) == 0)
    {
        if (S_ISDIR(path_stat.st_mode))
        {
            ft_putstr_fd("minishell: ", STDERR_FILENO);
            ft_putstr_fd(path, STDERR_FILENO);
            ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
            return(OK);
        }
    }
    return (ERR);
}

void free_argv_envp_exit(char **argv, char **envp, int exit_code)
{
    if (argv)
        free_strings_array(argv);
    if (envp)
        free_strings_array(envp);
    exit (exit_code);
}

char	*find_cmd_path(t_shell *shell)
{
    return (get_env_value(shell->env_list, "PATH"));
}

char	*build_full_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}