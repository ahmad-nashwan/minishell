# include "../../../inc/minishell.h"

t_string *get_var_name(t_string *line)
{
	t_string *name;

	name = new_string(32); // MALLOC_CHECK[OK]
	if (!name)
		return (NULL);
	while (ft_isalnum(peek(line)) || peek(line) == '_')
    {
		if (append(name, advance(line)) != OK)
        {
            free_t_string(name);
            return (NULL);
        }
    }   
	return (name);
}

t_code get_var_value(t_shell *shell, t_string *name, t_string **value)
{
    char    *raw_val;
    char    *dup;

    raw_val = get_env_value(shell->env_list, name->str);
    if (!raw_val)
    {
        *value = NULL;
        return (NONE);
    }
    dup = ft_strdup(raw_val);
    if (!dup)
        return (INTERNAL_ERROR);
    *value = init_string(dup);
    if (!*value)
    {
        free(dup);
        return (INTERNAL_ERROR);
    }
    return (OK);
}

t_code	init_expand(t_shell *shell, t_string *line, t_string *word, int quoted)
{
	t_code		rc;
	char		c;

	advance(line); // consume $
	c = peek(line);
	if (c == '?')
		rc = expand_exit_status(shell, line, word, quoted);
	else if(ft_isalpha(c) || c == '_')
		rc = find_variable_expand(shell, line, word, quoted);
	else
		rc = append(word, '$');
	return (rc);
}
