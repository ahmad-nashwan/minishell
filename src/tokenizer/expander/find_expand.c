# include "../../../inc/minishell.h"

t_code find_variable_expand(t_shell *shell, t_string *line, t_string *word, int quoted)
{
    t_string *name;
    t_string *value;
    t_code    rc;

    name = get_var_name(line); // MEMORY_CHECK[OK]
    if (!name)
        return (INTERNAL_ERROR);
    rc = get_var_value(shell, name, &value);
    free_t_string(name);
    if (rc == INTERNAL_ERROR)
        return (INTERNAL_ERROR);
    if (rc == NONE)
        return (OK); // variable not found → append nothing
    rc = expand_var(shell, word, value->str, quoted);
    free_t_string(value);
    return (rc);
}