#include "../../inc/minishell.h"

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

char	**list_to_array(t_list *list)
{
	t_list	*current;
	char	**argv;
	int		size;
	int		i;

	size = ft_lstsize(list);
	argv = malloc(sizeof(char *) * (size + 1));
	if (!argv)
		return (NULL);
	current = list;
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
