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

static void expand_tokens(t_string *word, t_shell *shell, char *value)
{
    char    **words;
    size_t  i;
    size_t  j;

    words = ft_split(value, ' ');
    if (!words)
        error_exit("Malloc Failure");
    j = 0;
    while (words[0][j])
        append(word, words[0][j++]);
    add_token(&shell->tokens, word->str, WORD);
    word->str = NULL;
    word->str = malloc(word->cap);
    word->len = 0;
    word->str[0] = '\0';
    i = 1;
    while (words[i])
    {
        add_token(&shell->tokens, words[i], WORD);
        i++;
    }
    free(words[0]);
    free(words);
}

static void	expand_variable(t_shell *shell, t_string *word, char *value, int quoted)
{
	size_t	i;
	if (!quoted && ft_strchr(value, ' '))
	{
		expand_tokens(word, shell, value);
	}
	else
	{
		i = 0;
		while (value[i])
		{
			append(word, value[i]);
			i++;
		}
	}
}

void	expand(t_shell *shell, t_string *line, t_string *word, int quoted)
{
	t_string	*name;
	t_string	*value;

	advance(line); // consume $
	if (peek(line) == '?')
	{
		advance(line);
		value = init_string(ft_itoa(shell->exit_status));
		expand_variable(shell, word, value->str, quoted);
		free_t_string(value);
	}
	else if(ft_isalpha(peek(line)) || peek(line) == '_')
	{
		name = get_var_name(line);
		if (!name)
			error_exit("Malloc failure");
		value = get_var_value(shell, name);
		if (value)
			expand_variable(shell, word, value->str, quoted);
		free_t_string(name);
		free_t_string(value);
	}
	else
		append(word, '$');
}
