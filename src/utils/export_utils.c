#include "../../inc/minishell.h"

static void	swap_env(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_env(char **sorted, size_t count)
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

void	print_env_entry(char *entry)
{
	char	*equal_sign;

	equal_sign = ft_strchr(entry, '=');
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	if (!equal_sign)
	{
		ft_putendl_fd(entry, STDOUT_FILENO);
		return ;
	}
	while (entry != equal_sign)
		ft_putchar_fd(*entry++, STDOUT_FILENO);
	ft_putstr_fd("=\"", STDOUT_FILENO);
	ft_putstr_fd(equal_sign + 1, STDOUT_FILENO);
	ft_putstr_fd("\"\n", STDOUT_FILENO);
}

t_code	print_export(t_shell *shell)
{
	char **sorted;
	size_t count;
	size_t i;

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
		print_env_entry(sorted[i]);
		i++;
	}
	free(sorted);
	return (OK);
}