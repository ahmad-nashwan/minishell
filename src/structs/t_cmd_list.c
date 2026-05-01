# include "../../inc/minishell.h"

int cmd_list_add(t_list **cmd_list, t_cmd *cmd)
{
    t_list *node;

    if (!cmd_list || !cmd)
        return (1);
    node = ft_lstnew((void *)cmd);
    if (!node)
        return (1);
    ft_lstadd_back(cmd_list, node);
    return (0);
}

void cmd_list_clear(t_list **cmd_list)
{
    ft_lstclear(cmd_list, cmd_free);
}