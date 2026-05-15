#include "../../inc/minishell.h"

t_code	excute_cmds(t_shell *shell)
{
	t_list	*cmd_node;
	t_cmd	*cmd;

	cmd_node = shell->cmds;
	while (cmd_node)
	{
		cmd = (t_cmd *)cmd_node->content;
		if (cmd->argv_list)
		{
			if (is_builtin((char *)cmd->argv_list->content))
				run_builtin(shell, cmd);
			else
				excuter(shell);
		}
		cmd_node = cmd_node->next;
	}
	return (OK);
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
	char	**argv;

	name = (char *)cmd->argv_list->content;
	argv = argv_list_to_array(cmd->argv_list);
	if (ft_strncmp(name, "env", 4) == 0)
		env(*shell);
	else if (ft_strncmp(name, "pwd", 4) == 0)
		pwd(STDOUT_FILENO);
	else if (ft_strncmp(name, "echo", 5) == 0)
		echo(argv, STDOUT_FILENO);
	else if (ft_strncmp(name, "cd", 3) == 0)
		cd(shell, argv);
	else if (ft_strncmp(name, "export", 7) == 0)
		export(shell, argv);
	else if (ft_strncmp(name, "unset", 6) == 0)
		unset(shell, argv);
	else if (ft_strncmp(name, "exit", 5) == 0)
		shell_exit(shell, argv);
	free(argv);
	return (OK);
}
