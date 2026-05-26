#include "../../inc/minishell.h"

void	pwd(t_shell *shell)
{
	char *env_pwd;
	char *wd;

	env_pwd = get_env_value(shell->env_list, "PWD");
		// Use your actual env fetcher
	if (env_pwd)
	{
		ft_putendl_fd(env_pwd, STDOUT_FILENO);
		return ;
	}
	wd = getcwd(NULL, 0);
	if (wd)
	{
		ft_putendl_fd(wd, STDOUT_FILENO);
		free(wd);
		shell->exit_status = 0;
		return ;
	}
	perror("minishell: pwd");
	shell->exit_status = 1;
}