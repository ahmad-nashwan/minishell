# include "../../inc/minishell.h"

t_code cmd_list_add(t_list **cmd_list, t_cmd *cmd)
{
    t_list *node;

    if (!cmd_list || !cmd)
        return (ERR);
    node = ft_lstnew((void *)cmd);
    if (!node)
        return (INTERNAL_ERROR);
    ft_lstadd_back(cmd_list, node);
    return (OK);
}

void cmd_list_clear(t_list **cmd_list)
{
    ft_lstclear(cmd_list, cmd_free);
}