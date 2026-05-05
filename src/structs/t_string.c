# include "../../inc/minishell.h"

t_string	*init_string(char *str)
{
    t_string *string;

    if (!str)
        return (NULL);
    string = malloc(sizeof(t_string));
    if (!string)
        return (NULL);
    string->index = 0;
    string->str = str;
    string->len = ft_strlen(str);
    string->cap = string->len + 1;
    return (string);
}

t_string	*new_string(size_t cap)
{
    t_string *string;

    string = malloc(sizeof(t_string));
    if (!string)
        return (NULL);
    string->index = 0;
    string->len = 0;
    string->cap = cap;
    string->str = malloc(cap);
    if (!string->str)
    {
        free(string);
        return (NULL);
    }
    string->str[0] = '\0';
    return (string);
}

char *realloc_string(t_string *word)
{
    size_t new_cap = word->cap * 2;
    void *ptr = realloc(word->str, new_cap);

    if (!ptr)
        return NULL;
    word->cap = new_cap;
    return ptr;
}

char	peek(t_string *line)
{
	if (line->index < line->len && line->str[line->index])
	{
		return (line->str[line->index]);
	}
	else
		return ('\0');
}

char	advance(t_string *line)
{
    if (line->index < line->len && line->str[line->index])
	    return (line->str[line->index++]);
    return ('\0');
}

t_code	append(t_string *word, char c)
{
	char	*ptr;

	if (word->len + 1 >= word->cap)
	{
		ptr = realloc_string(word);
		if (ptr == NULL)
			return (INTERNAL_ERROR);
		word->str = ptr;
	}
	word->str[word->len++] = c;
	word->str[word->len] = '\0';
    return (OK);
}

void    free_t_string(t_string *str)
{
    if (!str)
        return ;
    if (str->str)
        free(str->str);
    free(str);
}