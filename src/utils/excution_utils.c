#include "../../inc/minishell.h"

char* find_cmd_path(t_shell *shell)
{
	char **envvars = shell->env_vars;
	while (*envvars)
	{
		if (ft_strncmp(*envvars, "PATH=", 5) == 0)
		{
			return ft_strdup(*envvars + 5);
		}
		envvars++;
	}
	return NULL;
}

char    *build_full_path(char *dir, char *cmd)
{
    char    *temp;
    char    *full_path;

    temp = ft_strjoin(dir, "/");
    if (!temp)
        return (NULL);
    full_path = ft_strjoin(temp, cmd);
    free(temp);
    return (full_path);
}

char    **argv_list_to_array(t_list *argv_list)
{
    t_list  *current;
    char    **argv;
    int     size;
    int     i;

    size = ft_lstsize(argv_list);
    argv = malloc(sizeof(char *) * (size + 1));
    if (!argv)
        return (NULL);
    current = argv_list;
    i = 0;
    while (current)
    {
        argv[i] = (char *)current->content;
        current = current->next;
        i++;
    }
    argv[i] = NULL;
    return (argv);
}
