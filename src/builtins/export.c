#include "../../inc/minishell.h"

static char	*build_env_entry(char *name, char *value)
{
	char	*temp;
	char	*entry;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	entry = ft_strjoin(temp, value);
	free(temp);
	return (entry);
}

static t_code	update_env_var(t_shell *shell, char *name, char *value,
		size_t name_len)
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

static t_code	add_env_var(t_shell *shell, char *name, char *value,
		size_t env_count)
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

static t_code	process_export_arg(t_shell *shell, char *arg)
{
	char	*equal_sign;
	char	*name;
	char	*value;
	size_t	name_len;
	size_t	env_count;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (report_error(shell, BUILTIN_ERROR, "export: invalid argument"),
			BUILTIN_ERROR);
	name_len = equal_sign - arg;
	name = ft_substr(arg, 0, name_len);
	value = ft_strdup(equal_sign + 1);
	if (!name || !value)
		return (free(name), free(value), INTERNAL_ERROR);
	env_count = 0;
	while (shell->env_vars[env_count])
		env_count++;
	if (find_env_var(shell->env_vars, name, name_len) < env_count)
		update_env_var(shell, name, value, name_len);
	else
		add_env_var(shell, name, value, env_count);
	free(name);
	free(value);
	return (OK);
}

t_code	export(t_shell *shell, char **args)
{
	int		i;
	t_code	rc;

	if (!shell || !shell->env_vars || !args)
		return (INTERNAL_ERROR);
	i = 1;
	rc = OK;
	while (args[i] && rc == OK)
	{
		rc = process_export_arg(shell, args[i]);
		i++;
	}
	return (rc);
}
