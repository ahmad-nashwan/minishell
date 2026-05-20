#include "../../../inc/minishell.h"

static int is_valid_identifier(char *str)
{
    int i;

    if (!str || !(*str == '_' || ft_isalpha(*str)))
        return (0);
    i = 1;
    while (str[i] && str[i] != '=')
    {
        if (!(ft_isalnum(str[i]) || str[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}


static t_code export_without_value(t_list **env_list, char *arg)
{
    t_env_var   *var;

    if (find_env_var(*env_list, arg))
        return (OK); // Do nothing
    var = new_env_var(arg, NULL);
    if (!var)
        return (ERR);
    return (add_env_var(env_list, var));
}

static t_code export_with_value(t_list **env_list, char *arg, char *eq)
{
    char *key;
    t_env_var *var;

    key = ft_substr(arg, 0, eq - arg);
    if (!key)
        return (ERR);
    var = find_env_var(*env_list, key);
    if (var)
    {
        free(key);
        return (update_env_value(var, eq + 1)); // eq + 1 is the value
    }
    var = new_env_var(key, eq + 1); // Helper handles the key/value copy
    free(key); // new_env_var should have strdup'd the key already
    if (!var)
        return (ERR);
    return (add_env_var(env_list, var));
}

static t_code process_export(t_list **env_list, char *arg)
{
    char        *eq;

    eq = ft_strchr(arg, '=');
    if (!eq)
        return (export_without_value(env_list, arg));
    return (export_with_value(env_list, arg, eq));
}

t_code export_variables(t_shell *shell, t_list *args)
{
    t_code  final_status;

    final_status = OK;
    while (args)
    {
        if (!is_valid_identifier((char *)args->content))
        {
            ft_putstr_fd("minishell: export: `", STDERR_FILENO);
            ft_putstr_fd((char *)args->content, STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            final_status = ERR;
        }
        else
        {
            if (process_export(shell->env_list, (char *)args->content) != OK)
                final_status = ERR;
        }
        args = args->next;
    }
    if (final_status == OK)
        shell->exit_status = 0;
    else
        shell->exit_status = 1;
    return (final_status);
}
