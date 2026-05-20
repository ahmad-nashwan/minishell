#include "../../inc/minishell.h"

t_code	excuter(t_shell *shell)
{
	pid_t	p;
	int		status;

	p = fork();
	if (p == -1)
		return (-1);
	if (p == 0)
	{
		if (child_process(shell) == INTERNAL_ERROR)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (waitpid(p, &status, 0) == -1)
			return (-3);
		if (WIFSIGNALED(status))
			ft_putstr_fd("Process terminated by signal\n", STDERR_FILENO);
	}
	return (OK);
}

t_code	child_process(t_shell *shell)
{
	t_cmd	*cmd;
	char	**argv;
	char	**envp;

	cmd = (t_cmd *)shell->cmds->content;
	argv = argv_list_to_array(cmd->argv_list);
	if (!argv || !argv[0])
		return (INTERNAL_ERROR);
	envp = get_env_array(shell->env_list);
	if (!envp)
		return (INTERNAL_ERROR);
	if (ft_strchr(argv[0], '/'))
		return (exec_absolute_path(argv, envp));
	return (search_and_exec(shell, argv, envp));
}
t_code	exec_from_path(char **argv, char **path_list, char **envp)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_list[i])
	{
		full_path = build_full_path(path_list[i], argv[0]);
		if (full_path && access(full_path, X_OK) == 0)
		{
			execve(full_path, argv, envp);
			return (INTERNAL_ERROR);
		}
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) != 0)
			free(full_path);
		i++;
	}
	return (CMD_NOT_FOUND);
}

t_code	search_and_exec(t_shell *shell, char **argv, char **envp)
{
	char	**path_list;
	char	*cmd_path;

	cmd_path = find_cmd_path(shell);
	if (!cmd_path)
	{
		report_error(shell, CMD_NOT_FOUND, argv[0]);
		exit(EXIT_FAILURE);
	}
	path_list = ft_split(cmd_path, ':');
	if (!path_list)
	{
		report_error(shell, CMD_NOT_FOUND, argv[0]);
		exit(EXIT_FAILURE);
	}
	return (exec_from_path(argv, path_list, envp));
}

t_code	exec_absolute_path(char **argv, char **envp)
{
	if (access(argv[0], F_OK) == 0)
	{
		if (access(argv[0], X_OK) == 0)
			return (execve(argv[0], argv, envp));
		else
			return (PERMISSION_DENIED);
	}
	return (CMD_NOT_FOUND);
}