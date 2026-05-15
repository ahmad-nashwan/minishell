#include "../../inc/minishell.h"

static char	*get_cd_target(t_shell *shell, char **args)
{
	char	*home;

	if (args[1])
		return (args[1]);
	home = get_env_value(shell->env_vars, "HOME");
	if (!home)
		report_error(shell, ERR, "cd: HOME not set");
	return (home);
}

t_code	cd(t_shell *shell, char **args)
{
	char	*target;

	if (!shell || !shell->env_vars || !args)
		return (INTERNAL_ERROR);
	target = get_cd_target(shell, args);
	if (!target)
		return (BUILTIN_ERROR);
	if (chdir(target) == -1)
	{
		report_error(shell, ERR, target);
		return (BUILTIN_ERROR);
	}
	if (shell->cwd)
		free(shell->cwd);
	shell->cwd = getcwd(NULL, 0);
	return (OK);
}
