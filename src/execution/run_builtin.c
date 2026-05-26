#include "../../inc/minishell.h"

t_code	run_builtin(t_shell *shell, t_cmd *cmd)
{
	char	*name;

	if (!cmd->argv_list)
		return (ERR);
	name = (char *)cmd->argv_list->content;
	if (ft_strncmp(name, "echo", 5) == 0)
		echo(shell, cmd->argv_list);
	else if (ft_strncmp(name, "cd", 3) == 0)
		cd(shell, cmd->argv_list);
	else if (ft_strncmp(name, "pwd", 4) == 0)
		pwd(shell);
	else if (ft_strncmp(name, "export", 7) == 0)
		export(shell, cmd->argv_list);
	else if (ft_strncmp(name, "unset", 6) == 0)
		unset(shell, cmd->argv_list);
	else if (ft_strncmp(name, "env", 4) == 0)
		env(shell, cmd->argv_list);
	else if (ft_strncmp(name, "exit", 5) == 0)
		shell_exit(shell, cmd->argv_list);
	else
		return (NONE);
	return (OK);
}
