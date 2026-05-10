#include "../../inc/minishell.h"

void env(t_shell shell)
{
	char **tmp_env_vars;
	char *env_var;

	tmp_env_vars = shell.env_vars;
	while (tmp_env_vars)
	{
		env_var = *tmp_env_vars;
		ft_printf("%s\n",env_var);
		tmp_env_vars++;
	}
}
