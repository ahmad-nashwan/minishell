# include "../../inc/minishell.h"

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	*get_env_value(char **env_vars, const char *key)
{
	size_t	key_len;
	int	i;

	if (!env_vars || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (env_vars[i])
	{
		if (ft_strncmp(env_vars[i], key, key_len) == 0
			&& env_vars[i][key_len] == '=')
			return (env_vars[i] + key_len + 1);
		i++;
	}
	return (NULL);
}
