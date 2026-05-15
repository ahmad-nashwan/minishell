#include "../../inc/minishell.h"

t_code export(t_shell *shell, char **args)
{
    int i = 1;
    while (args && args[i])
    {
        char *arg = args[i];
        char *equal_sign = ft_strchr(arg, '=');
        if (!equal_sign)
        {
            report_error(shell, BUILTIN_ERROR, "export: invalid argument");
            return BUILTIN_ERROR;
        }
        size_t name_len = equal_sign - arg;
        char *name = ft_substr(arg, 0, name_len);
        char *value = ft_strdup(equal_sign + 1);
        if (!name || !value)
        {
            free(name);
            free(value);
            report_error(shell, INTERNAL_ERROR, "export: memory allocation failed");
            return INTERNAL_ERROR;
        }
        // Check if variable already exists
        char *existing_value = get_env_value(shell->env_vars, name);
        if (existing_value)
        {
            // Update existing variable
            size_t existing_index = 0;
            while (shell->env_vars[existing_index])
            {
                if (ft_strncmp(shell->env_vars[existing_index], name, name_len) == 0
                    && shell->env_vars[existing_index][name_len] == '=')
                {
                    free(shell->env_vars[existing_index]);
                    char *temp = ft_strjoin(name, "=");
                    char *temp1 = ft_strjoin(temp, value);
                    shell->env_vars[existing_index] = ft_strdup(temp1);
                    free(temp1);
                    free(temp);
                    break;
                }
                existing_index++;
            }
        }
        else
        {
            // Add new variable
            size_t env_count = 0;
            while (shell->env_vars && shell->env_vars[env_count])
                env_count++;
            char **new_env = malloc(sizeof(char *) * (env_count + 2));
            if (!new_env)
            {
                free(name);
                free(value);
                report_error(shell, INTERNAL_ERROR, "export: memory allocation failed");
                return INTERNAL_ERROR;
            }
            for (size_t j = 0; j < env_count; j++)
                new_env[j] = shell->env_vars[j];
            char *temp = ft_strjoin(name, "=");
            char *temp1 = ft_strjoin(temp, value);
            new_env[env_count] = ft_strdup(temp1);
            new_env[env_count + 1] = NULL;
            free(temp);
            free(temp1);
            free(shell->env_vars);
            shell->env_vars = new_env;
        }
        free(name);
        free(value);
        i++;
    }
    return OK;
}
