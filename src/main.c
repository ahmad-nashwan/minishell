# include "../inc/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell shell;

	if (argc > 1)
		error_exit("usage: ./minishell");
	
	init_shell(&shell, envp);
	start_shell(&shell);
	(void)argv;
	return (0);
}