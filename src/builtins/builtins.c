#include "../../inc/minishell.h"

void env(t_shell shell)
{
    void **envp = (void **) shell.env_vars;
    while (*envp)
    {
        ft_putendl_fd((char *) *envp, STDOUT_FILENO);
        envp++;
    }
}
