#include "../../inc/minishell.h"

static void unset_env_var(t_list **env_list, char *key)
{
    t_list      *prev;
    t_list      *node;
    t_env_var   *var;

    if (!env_list || !*env_list)
        return ;
    prev = NULL;
    node = *env_list;
    while (node)
    {
        var = (t_env_var *)node->content;
        if (ft_strcmp(var->key, key) == 0)
        {
            if (prev)
                prev->next = node->next;
            else
                *env_list = node->next;
            ft_lstdelone(node, free_env_var);
            return ;
        }
        prev = node;
        node = node->next;
    }
}

void	unset(t_shell *shell, t_list *args)
{
	char *key;

	if (!shell || !args)
	{
		report_error(shell, INTERNAL_ERROR, "Invalid pointer");
		return ;
	}
	args = args->next; // skipping the unset command string
	while (args)
	{
		key = (char *)args->content;
		unset_env_var(&shell->env_list, key);
		args = args->next;
	}
}
