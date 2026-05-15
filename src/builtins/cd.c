#include "../../inc/minishell.h"

t_code cd(t_shell *shell, char **args)
{
    char *target = NULL;
    char *home = NULL;

    if (args && args[1])
        target = args[1];
    else
    {
        home = get_env_value(shell->env_vars, "HOME");
        if (!home)
        {
            report_error(shell, ERR, "cd: HOME not set");
            return BUILTIN_ERROR;
        }
        target = home;
    }
    if (chdir(target) == -1)
    {
        report_error(shell, ERR, target);
        return BUILTIN_ERROR;
    }
    if (shell->cwd)
        free(shell->cwd);
    shell->cwd = getcwd(NULL, 0);
    return OK;
}
