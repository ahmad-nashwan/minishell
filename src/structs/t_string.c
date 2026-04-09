# include "../../inc/minishell.h"

t_string *init_string(char *content)
{
    t_string *string;

    string = malloc(sizeof(t_string));
    if (!string)
        return NULL;
    string->index = 0;
    if (content)
    {
		string->len = ft_strlen(content);
        string->cap = string->len + 1 ;
        string->str = strdup(content);
        if (!string->str)
		{
			free(string);
			return (NULL);
		}
    }
    else
    {
        string->cap = 1024;
		string->len = 0;
        string->str = malloc(string->cap);
        if (!string->str)
            return (free(string), NULL);
        string->str[0] = '\0';
    }
    return string;
}

char *realloc_string(t_string *word)
{
    void *ptr;

    if (word->cap == 0)
        word->cap = 16;

    if (word->len < word->cap)
        return word->str;
    word->cap *= 2;
    ptr = realloc(word->str, word->cap);
    if (!ptr)
        return NULL;
    word->str = ptr;
    return word->str;
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
	return (line->index++);
}
