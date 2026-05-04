# include "../../inc/minishell.h"

void	error_exit(char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
	exit(1);
}

static int error_to_exit_code(t_error e)
{
    if (e == ERR_NONE)
        return (0);
    if (e == ERR_SYNTAX)
        return (2);
    if (e == ERR_CMD_NOT_FOUND)
        return (127);
    if (e == ERR_NO_SUCH_FILE)
        return (127);
    if (e == ERR_PERMISSION)
        return (126);
    if (e == ERR_MALLOC)
        return (1);
    if (e == ERR_EXECVE)
        return (1);
    if (e == ERR_BUILTIN)
        return (1);
    return (1);
}

void	report_error(t_shell *shell, t_error e, char *msg)
{
	shell->error_type = e;
	shell->exit_status = error_to_exit_code(e);
	if (e == ERR_MALLOC)
		shell->should_exit = 1;
	if (msg)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd(msg, 2);
	}
}