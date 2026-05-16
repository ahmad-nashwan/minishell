#include "../../inc/minishell.h"

static char	*build_env_entry(char *name, char *value)
{
	char	*temp;
	char	*entry;

	if (!value)
		return (ft_strdup(name));
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	entry = ft_strjoin(temp, value);
	free(temp);
	return (entry);
}

size_t	find_env_var(char **env_vars, char *name, size_t name_len)
{
	size_t	i;

	i = 0;
	while (env_vars[i])
	{
		if (ft_strncmp(env_vars[i], name, name_len) == 0
			&& (env_vars[i][name_len] == '=' || env_vars[i][name_len] == '\0'))
			return (i);
		i++;
	}
	return (i);
}

t_code	update_env_var(t_shell *shell, char *name, char *value, size_t name_len)
{
	size_t	i;
	char	*entry;

	i = 0;
	while (shell->env_vars[i])
	{
		if (ft_strncmp(shell->env_vars[i], name, name_len) == 0
			&& shell->env_vars[i][name_len] == '=')
		{
			entry = build_env_entry(name, value);
			if (!entry)
				return (INTERNAL_ERROR);
			free(shell->env_vars[i]);
			shell->env_vars[i] = entry;
			return (OK);
		}
		i++;
	}
	return (OK);
}

t_code	add_env_var(t_shell *shell, char *name, char *value, size_t env_count)
{
	char	**new_env;
	char	*entry;
	size_t	j;

	new_env = malloc(sizeof(char *) * (env_count + 2));
	if (!new_env)
		return (INTERNAL_ERROR);
	j = 0;
	while (j < env_count)
	{
		new_env[j] = shell->env_vars[j];
		j++;
	}
	entry = build_env_entry(name, value);
	if (!entry)
		return (free(new_env), INTERNAL_ERROR);
	new_env[env_count] = entry;
	new_env[env_count + 1] = NULL;
	free(shell->env_vars);
	shell->env_vars = new_env;
	return (OK);
}

size_t	count_env(char **env_vars)
{
	size_t	count;

	count = 0;
	while (env_vars[count])
		count++;
	return (count);
}
