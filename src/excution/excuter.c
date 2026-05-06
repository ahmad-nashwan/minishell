#include "../../inc/minishell.h"

void excuter(t_shell *shell)
{
	pid_t p;

	p = fork();

	if (p == 0)
	{
		excute (shell->cmds);
	}
	else
	{
		wait(NULL);
	}
}
