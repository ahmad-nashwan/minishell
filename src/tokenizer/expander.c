# include "../../inc/minishell.h"

static t_string *get_var_name(t_string *line)
{
	t_string *name;

	name = new_string(32);
	if (!name)
		return (NULL);
	while (ft_isalnum(peek(line)) || peek(line) == '_')
		append(name, advance(line));
	return (name);
}

static t_string *get_var_value(t_shell *shell, t_string *name)
{
	t_string 	*value;
	size_t		i;
	size_t		len;

	i = 0;
	len = ft_strlen(name->str);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name->str, len) == 0 && shell->env[i][len] == '=')
		{
			value = init_string(ft_strdup(shell->env[i] + len + 1));
			if (!value)
				error_exit("Malloc failure");
			return (value);
		}
		i++;
	}
	return (NULL);
}

void	expand_variable(t_string *word, char *value)
{
	size_t	i;

	i = 0;
	while (value[i])
	{
		append(word, value[i]);
		i++;
	}
}

void	expand(t_shell *shell, t_string *line, t_string *word)
{
	t_string	*name;
	t_string	*value;

	advance(line); // consume $
	if (peek(line) == '?')
	{
		advance(line);
		value = init_string(ft_itoa(shell->exit_status));
		expand_variable(word, value->str);
		free_t_string(value);
	}
	else if(ft_isalpha(peek(line)) || peek(line) == '_')
	{
		name = get_var_name(line);
		if (!name)
			error_exit("Malloc failure");
		value = get_var_value(shell, name);
		if (value)
			expand_variable(word, value->str);
		free_t_string(name);
		free_t_string(value);
	}
	else
		append(word, '$');
}
