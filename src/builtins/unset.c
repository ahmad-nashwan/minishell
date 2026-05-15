#include "../../inc/minishell.h"

t_code unset(t_shell *shell, char **args)
{
	int		i;
	int		j;
	size_t	name_len;
	size_t	env_count;

	if (!shell || !shell->env_vars || !args)
		return (OK);
	i = 1;
	while (args && args[i])
	{
		name_len = ft_strlen(args[i]);
		j = 0;
		while (shell->env_vars[j])
		{
			if (ft_strncmp(shell->env_vars[j], args[i], name_len) == 0
				&& shell->env_vars[j][name_len] == '=')
			{
				free(shell->env_vars[j]);
				env_count = j;
				while (shell->env_vars[env_count])
				{
					shell->env_vars[env_count] = shell->env_vars[env_count + 1];
					env_count++;
				}
				break;
			}
			j++;
		}
		i++;
	}
	return (OK);
}
