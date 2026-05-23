# include "../../../inc/minishell.h"

void free_array(char **arr, int elements)
{
    int i;

    if (!arr)
        return ;
    i = 0;
    while (i < elements)
    {
        if (arr[i])
            free(arr[i]);
        i++;
    }
}

static char *get_var_str(t_env_var *var)
{
    char    *str;
    char    *temp;

    if (var->key && var->value)
    {
        temp = ft_strjoin(var->key, "=");
        if (!temp)
            return (NULL);
        str = ft_strjoin(temp, var->value);
        free(temp); 
    }
    else
    {
        str = ft_strdup(var->key);
    }
    if (!str)
        return (NULL);
    return (str);
}

static t_code fill_array(t_list *env_list, char **arr, int size)
{
    t_env_var   *var;
    t_list      *node;
    int         i;

    i = 0;
    node = env_list;
    while (node && i < size)
    {
        var = (t_env_var *) node->content;
        arr[i] = get_var_str(var);
        if (!arr[i])
        {
            free_array(arr, i);
            return (ERR);
        }
        i++;
        node = node->next;
    }
    return (OK);
}


/*
Changes to this function:
env_list being null does not mean that envp can be null
envp should be a valid memory address
if env_list is null, or empty
we should still allocate memory for envp
because passing NULL to execve would be undefined behavior
To do: Check the validity of this function usage across the program
*/
char    **get_env_array(t_list *env_list)
{
    int size;
    char    **arr;

    if (!env_list)
    {
        arr = malloc(sizeof(char *) * 1);
        if (!arr)
            return (NULL);
        arr[0] = NULL;
        return (arr);
    }
    size = ft_lstsize(env_list);
    arr = malloc(sizeof(char *) * (size + 1));
    if (!arr)
        return (NULL);
    arr[size] = NULL;
    if (fill_array(env_list, arr, size) == ERR)
    {
        free(arr);
        return (NULL);
    }
    return (arr);
}
