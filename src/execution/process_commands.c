#include "../../inc/minishell.h"

t_code	process_commands(t_shell *shell)
{
	t_cmd	*cmd;

	if (ft_lstsize(shell->cmds) == 1)
	{
		cmd = (t_cmd *)shell->cmds->content;
		if (cmd->argv_list && is_builtin((char *)cmd->argv_list->content))
		{
			if (handle_redirections(shell, cmd) == ERR)
				return (ERR);
			run_builtin(shell, cmd);
			return (OK);
		}
	}
	return (process_pipeline(shell));
}

int	is_builtin(char *name)
{
	if (ft_strncmp(name, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(name, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(name, "export", 7) == 0)
		return (1);
	if (ft_strncmp(name, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(name, "env", 4) == 0)
		return (1);
	if (ft_strncmp(name, "exit", 5) == 0)
		return (1);
	return (0);
}

t_code	run_builtin(t_shell *shell, t_cmd *cmd)
{
	char	*name;

	name = (char *)cmd->argv_list->content;
	if (ft_strncmp(name, "env", 4) == 0)
		env(shell, cmd->argv_list);
	else if (ft_strncmp(name, "pwd", 4) == 0)
		pwd(shell);
	else if (ft_strncmp(name, "echo", 5) == 0)
		echo(shell, cmd->argv_list);
	else if (ft_strncmp(name, "cd", 3) == 0)
		cd(shell, cmd->argv_list);
	else if (ft_strncmp(name, "export", 7) == 0)
		export(shell, cmd->argv_list);
	else if (ft_strncmp(name, "unset", 6) == 0)
		unset(shell, cmd->argv_list);
	else if (ft_strncmp(name, "exit", 5) == 0)
		shell_exit(shell, cmd->argv_list);
	else
		return (NONE);
	return (OK);
}
