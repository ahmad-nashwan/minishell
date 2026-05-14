# include "../../inc/minishell.h"

void	error_exit(char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
	exit(1);
}

static int error_to_exit_code(t_code e)
{
    if (e == NONE)
        return (0);
    if (e == SYNTAX_ERROR)
        return (2);
    if (e == CMD_NOT_FOUND)
        return (127);
    if (e == PERMISSION_DENIED)
        return (126);
    if (e == INTERNAL_ERROR)
        return (1);
    if (e == EXEC_ERROR)
        return (1);
    if (e == BUILTIN_ERROR)
        return (1);
    return (1);
}

void	report_error(t_shell *shell, t_code e, char *msg)
{
	shell->error_type = e;
	shell->exit_status = error_to_exit_code(e);
	if (e == INTERNAL_ERROR)
		shell->should_exit = 1;
	if (msg)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd(msg, 2);
	}
}

t_code  handle_error(t_shell *shell)
{
    if (shell->should_exit)
        return (ERR);
    return (OK);
}