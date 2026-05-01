# include "../../inc/minishell.h"

t_cmd *cmd_create()
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->argv_list = NULL;
    cmd->redirections = NULL;
    return (cmd);
}

int cmd_add_arg(t_cmd *cmd, char *lexeme)
{
    t_list  *node;
    char    *dup;
    if (!cmd || !lexeme)
        return (1);
    dup = ft_strdup(lexeme);
    if (!dup)
        return (1);
    node = ft_lstnew(dup);
    if (!node)
    {
        free(dup);
        return (1);
    }
    ft_lstadd_back(&cmd->argv_list, node);
    return (0);
}

int cmd_add_redir(t_cmd *cmd, t_redir *redir)
{
    t_list *node;

    if (!cmd || !redir)
        return (1);
    node = ft_lstnew((void *)redir);
    if (!node)
        return (1);
    ft_lstadd_back(&cmd->redirections, node);
    return (0);
}

void cmd_free(t_cmd *cmd)
{
    if (!cmd)
        return;
    if (cmd->argv_list)
        ft_lstclear(&cmd->argv_list, free);
    if (cmd->redirections)
        ft_lstclear(&cmd->redirections, redir_free);
    free(cmd);
}
