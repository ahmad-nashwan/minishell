# include "../../../inc/minishell.h"

static t_code append_extra_words(t_shell *shell, char **words)
{
    size_t i;

    i = 1;
    while (words[i])
    {
        if (add_token(&shell->tokens, words[i], WORD, 0) != OK)
            return INTERNAL_ERROR;
        i++;
    }
    return OK;
}

t_code append_str(t_string *word, char *s)
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

static t_code finalize_first_word(t_shell *shell, t_string *word)
{
    if (add_token(&shell->tokens, word->str, WORD, 0) != OK)
        return (INTERNAL_ERROR);
    word->str = NULL;
    return (reset_word(word));
}

t_code expand_split(t_string *word, t_shell *shell, char *value)
{
    char    **words;
    t_code  rc;

    words = ft_split(value, ' ');
    if (!words)
        return (INTERNAL_ERROR);
    if (!words[0])
    {
        free(words);
        return (OK); // Nothing to append, no extra words, safe exit!
    }
    rc = append_str(word, words[0]);
    free(words[0]);
    if (rc != OK)
    {
        free_split(words);
        return (INTERNAL_ERROR);
    }
    rc = finalize_first_word(shell, word);
    if (rc != OK)
    {
        free_split(words);
        return (INTERNAL_ERROR);
    }
    rc = append_extra_words(shell, words);
    free(words);
    return (rc);
}
