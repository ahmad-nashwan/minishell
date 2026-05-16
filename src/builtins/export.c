#include "../../inc/minishell.h"

static void	swap_env(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	sort_env(char **sorted, size_t count)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strncmp(sorted[j], sorted[j + 1], INT_MAX) > 0)
				swap_env(&sorted[j], &sorted[j + 1]);
			j++;
		}
		i++;
	}
}

static t_code	print_export(t_shell *shell)
{
	char	**sorted;
	size_t	count;
	size_t	i;

	count = count_env(shell->env_vars);
	sorted = malloc(sizeof(char *) * (count + 1));
	if (!sorted)
		return (INTERNAL_ERROR);
	i = 0;
	while (i < count)
	{
		sorted[i] = shell->env_vars[i];
		i++;
	}
	sorted[count] = NULL;
	sort_env(sorted, count);
	i = 0;
	while (sorted[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(sorted[i], STDOUT_FILENO);
		i++;
	}
	free(sorted);
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
