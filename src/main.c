#include "../inc/minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	int exit_status;
	if (argc > 1)
		error_exit("usage: ./minishell");

	init_shell(&shell, envp);
	exit_status = start_shell(&shell);
	(void)argv;
	return (exit_status);
}