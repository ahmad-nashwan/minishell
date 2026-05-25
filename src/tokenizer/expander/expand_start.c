# include "../../../inc/minishell.h"

t_string *get_var_name(t_string *line)
{
	t_string *name;

	name = create_empty_string(32); // MALLOC_CHECK[OK]
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

t_code	expand_start(t_shell *shell, t_string *line, t_string *word, int quoted)
{
	char	c;

	advance(line);
	c = peek(line);
	if (c == '?')
		return (expand_exit_status(shell, line, word, quoted));
	if (c == '0')
	{
		advance(line);
		return (append_str(word, "minishell"));
	}
	if (ft_isdigit(c))
	{
		advance(line);
		return (OK);
	}
	if (ft_isalpha(c) || c == '_')
		return (find_var_expand(shell, line, word, quoted));
	return (append(word, '$'));
}
