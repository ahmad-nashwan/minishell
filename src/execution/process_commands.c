#include "../../inc/minishell.h"

static t_code	process_single_builtin(t_shell *shell, t_cmd *cmd)
{
	int saved_stdout;
	int saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdout == -1 || saved_stdin == -1)
	{
		report_error(shell, INTERNAL_ERROR, "dup failed");
		return (ERR);
	}
	if (handle_redirections(cmd) == ERR)
	{
		close(saved_stdout);
		close(saved_stdin);
		return (ERR);
	}
	run_builtin(shell, cmd);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1 || dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		report_error(shell, INTERNAL_ERROR, NULL);	
		close(saved_stdout);
		close(saved_stdin);
		return (ERR);
	}
	close(saved_stdout);
	close(saved_stdin);
	return (OK);
}

t_code	process_commands(t_shell *shell)
{
	t_cmd	*cmd;

	if (ft_lstsize(shell->cmds) == 1)
	{
		cmd = (t_cmd *)shell->cmds->content;
		if (cmd->argv_list && is_builtin((char *)cmd->argv_list->content))
			return (process_single_builtin(shell, cmd));
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
