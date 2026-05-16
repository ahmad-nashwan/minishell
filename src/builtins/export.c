#include "../../inc/minishell.h"

static t_code	export_no_value(t_shell *shell, char *arg, size_t env_count)
{
	size_t	name_len;

	name_len = ft_strlen(arg);
	if (find_env_var(shell->env_vars, arg, name_len) < env_count)
		return (OK);
	return (add_env_var(shell, arg, NULL, env_count));
}

static t_code	export_with_value(t_shell *shell, char *arg, char *equal_sign,
		size_t env_count)
{
	char	*name;
	char	*value;
	size_t	name_len;

	name_len = equal_sign - arg;
	name = ft_substr(arg, 0, name_len);
	value = ft_strdup(equal_sign + 1);
	if (!name || !value)
		return (free(name), free(value), INTERNAL_ERROR);
	if (find_env_var(shell->env_vars, name, name_len) < env_count)
		update_env_var(shell, name, value, name_len);
	else
		add_env_var(shell, name, value, env_count);
	free(name);
	free(value);
	return (OK);
}

static t_code	process_export_arg(t_shell *shell, char *arg)
{
	char	*equal_sign;
	size_t	env_count;

	env_count = count_env(shell->env_vars);
	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (export_no_value(shell, arg, env_count));
	return (export_with_value(shell, arg, equal_sign, env_count));
}

t_code	export(t_shell *shell, char **args)
{
	int		i;
	t_code	rc;

	if (!shell || !shell->env_vars || !args)
		return (INTERNAL_ERROR);
	if (!args[1])
		return (print_export(shell));
	i = 1;
	rc = OK;
	while (args[i] && rc == OK)
	{
		rc = process_export_arg(shell, args[i]);
		i++;
	}
	return (rc);
}
