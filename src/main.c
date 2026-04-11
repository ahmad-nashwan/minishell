# include "../inc/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell shell;

	shell.env = NULL;
	shell.tokens = NULL;
	shell.exit_status = 0;
	if (argc > 1)
		error_exit("usage: ./minishell");
	shell.env = copy_env(envp);
	if (!shell.env)
		error_exit("Malloc failure.");
	start_shell(&shell);
	(void)argv;
	return (0);
}