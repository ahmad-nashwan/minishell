#include "../../inc/minishell.h"

static void	remove_env_var(char **env_vars, size_t index)
{
	free(env_vars[index]);
	while (env_vars[index])
	{
		env_vars[index] = env_vars[index + 1];
		index++;
	}
}

t_code	unset(t_shell *shell, char **args)
{
	int		i;
	size_t	name_len;
	size_t	index;

	if (!shell || !shell->env_vars || !args)
		return (INTERNAL_ERROR);
	i = 1;
	while (args[i])
	{
		name_len = ft_strlen(args[i]);
		index = find_env_var(shell->env_vars, args[i], name_len);
		if (shell->env_vars[index])
			remove_env_var(shell->env_vars, index);
		i++;
	}
	return (OK);
}
