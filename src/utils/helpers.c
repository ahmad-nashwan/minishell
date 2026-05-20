#include "../../inc/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r')
		return (1);
	return (0);
}

char	**copy_env(char **envp)
{
	int		var;
	int		i;
	char	**env;

	var = 0;
	while (envp[var])
		var++;
	env = malloc(sizeof(char *) * (var + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (i < var)
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			while (i > 0)
				free(env[--i]);
			free(env);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	free_split(char **words)
{
	size_t	i;

	i = 0;
	if (!words)
		return ;
	while (words[i])
		free(words[i++]);
	free(words);
}

int is_number(char *arg)
{
    int i;

    i = 0;
    while (arg[i] == ' ' || (arg[i] >= '\t' && arg[i] <= '\r'))
        i++;
    if (arg[i] == '-' || arg[i] == '+')
        i++;
    if (!ft_isdigit(arg[i]))
        return (0);
    while (ft_isdigit(arg[i]))
        i++;
    while (arg[i] == ' ' || (arg[i] >= '\t' && arg[i] <= '\r'))
        i++;
    if (arg[i] == '\0')
        return (1);
    return (0);
}

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 - (unsigned char)*s2);
}