# include "../../inc/minishell.h"

static t_code  close_and_return(int saved_stdout, int saved_stdin, t_code status)
{
    close(saved_stdout);
    close(saved_stdin);
    return (status);
}

t_code	process_single_builtin(t_shell *shell, t_cmd *cmd)
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
		return (close_and_return(saved_stdout, saved_stdin, ERR));
	run_builtin(shell, cmd);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1 || dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		report_error(shell, INTERNAL_ERROR, NULL);	
		return (close_and_return(saved_stdout, saved_stdin, ERR));
	}
	return (close_and_return(saved_stdout, saved_stdin, OK));
}
