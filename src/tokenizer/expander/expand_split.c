# include "../../../inc/minishell.h"

static t_code append_extra_words(t_shell *shell, char **words)
{
    size_t i;

    i = 1;
    while (words[i])
    {
        if (add_token(&shell->tokens, words[i], WORD) != OK)
            return INTERNAL_ERROR;
        i++;
    }
    return OK;
}

static t_code append_to_word(t_string *word, char *s)
{
    size_t i;

    i = 0;
    while (s[i])
    {
        if (append(word, s[i]) != OK)
            return (INTERNAL_ERROR);
        i++;
    }
    return (OK);
}

static t_code reset_word(t_string *word)
{
    char *new;

    new = malloc(word->cap); // MEMORY_CHECK[OK]
    if (!new)
        return INTERNAL_ERROR;
    word->str = new;
    word->len = 0;
    word->str[0] = '\0';
    return OK;
}
t_code expand_split(t_string *word, t_shell *shell, char *value)
{
    char    **words;
    t_code  rc;

    words = ft_split(value, ' '); // MEMORY_CHECK[OK]
    if (!words)
        return (INTERNAL_ERROR);
    rc = append_to_word(word, words[0]);
    if (rc != OK)
    {
        free_split(words);
        return (INTERNAL_ERROR);
    }
    if (add_token(&shell->tokens, word->str, WORD) != OK)
    {
        free_split(words);
        return (INTERNAL_ERROR);
    }
    word->str = NULL;
    rc = reset_word(word);
    if (rc != OK)
    {
        free_split(words);
        return (INTERNAL_ERROR);
    }
    rc = append_extra_words(shell, words);
    if (rc != OK)
    {
        free_split(words);
        return (INTERNAL_ERROR);
    }
    free(words[0]);
    free(words);
    return (OK);
}

t_code	expand_var(t_shell *shell, t_string *word, char *value, int quoted)
{
	size_t	    i;
    t_code     rc;

    rc = OK;
    if (!quoted && ft_strchr(value, ' '))
	{
		rc = expand_split(word, shell, value);
	}
	else
	{
		i = 0;
		while (value[i])
		{
			rc = append(word, value[i]);
            if (rc != OK)
                return (rc);
			i++;
		}
	}
    return (rc);
}
