# include "../../../inc/minishell.h"

t_code find_variable_expand(t_shell *shell, t_string *line, t_string *word, int quoted)
{
    t_string    *name;
    char        *value;
    t_code      rc;

    name = get_var_name(line);
    if (!name)
        return (INTERNAL_ERROR);
    value = get_env_value(shell->env_list, name->str);
    free_t_string(name);
    if (!value)
        return (OK); // variable not found → append nothing
    rc = expand_var(shell, word, value, quoted);
    return (rc);
}