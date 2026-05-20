#include "../../inc/minishell.h"

static char *get_cd_target(t_shell *shell, t_list *args)
{
    char    *home;

    args = args->next;
    if (args && args->next)
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
        shell->exit_status = 1;
        return (NULL);
    }
    if (args)
        return ((char *)args->content);
    home = get_env_value(shell->env_list, "HOME");
    if (!home)
    {
        ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
        shell->exit_status = 1;
    }
    return (home);
}
static t_code update_pwd(t_list **env_list, char *new_pwd, char *old_pwd)
{
    t_env_var   *var;

    if (old_pwd)
    {
        var = find_env_var(*env_list, "OLDPWD");
        if (var)
            update_env_value(var, old_pwd);
        else
        {
            var = new_env_var("OLDPWD", old_pwd);
            if (!var)
                return (INTERNAL_ERROR);
            add_env_var(env_list, var);
        }
    }
    var = find_env_var(*env_list, "PWD");
    if (var)
        return (update_env_value(var, new_pwd));
    var = new_env_var("PWD", new_pwd);
    if (!var)
        return (INTERNAL_ERROR);
    return (add_env_var(env_list, var));
}

void  cd(t_shell *shell, t_list *args)
{
    char    *target;
    char    *old_pwd;
    char    *new_pwd;

    target = get_cd_target(shell, args);
    if (!target)
        return ;
    old_pwd = get_env_value(shell->env_list, "PWD");
    if (chdir(target) == -1)
    {
        perror("minishell: cd");
        shell->exit_status = 1;
        return ;
    }
    new_pwd = getcwd(NULL, 0);
    if (!new_pwd)
    {
        perror("minishell: cd");
        shell->exit_status = 1;
        return ;
    }
    shell->exit_status = 0;
    if (update_pwd(&shell->env_list, new_pwd, old_pwd) != OK)
        report_error(shell, INTERNAL_ERROR, "Malloc Failure");
    free(new_pwd);
}
