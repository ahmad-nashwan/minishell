# include "../../inc/minishell.h"

void	error_report(t_shell *shell,char *error, int state)
{
	shell->exit_status = state;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
}

void	error_exit(char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
	exit(1);
}
