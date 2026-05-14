# include "../../../inc/minishell.h"

t_code expand_exit_status(t_shell *shell, t_string *line, t_string *word, int quoted)
{
	char	    *value;
	t_code		rc;

	advance(line); // consume ?
	value = ft_itoa(shell->exit_status); // MEMORY_CHECK[OK]
	if (!value)
		return (INTERNAL_ERROR);
	rc = expand_var(shell, word, value, quoted);
	free(value);
	return (rc);
}
