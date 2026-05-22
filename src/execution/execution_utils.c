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

