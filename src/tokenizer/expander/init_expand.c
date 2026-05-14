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
    size_t i = 0;
    size_t len = ft_strlen(name->str);
    char   *dup;

    while (shell->env_vars[i])
    {
        if (ft_strncmp(shell->env_vars[i], name->str, len) == 0
            && shell->env_vars[i][len] == '=')
        {
            dup = ft_strdup(shell->env_vars[i] + len + 1); // MALLOC_CHECK[OK]
            if (!dup)
                return (INTERNAL_ERROR);
            *value = init_string(dup); // MALLOC_CHECK[OK]
            if (!*value)
            {
                free(dup);
                return (INTERNAL_ERROR);
            }
            return (OK);
        }
        i++;
    }
    *value = NULL;
    return (NONE);
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
