# include "../../inc/minishell.h"

void    print_cmds(t_list *cmds)
{
    t_list  *cmd_node;
    t_list  *arg_node;
    t_list  *redir_node;
    t_cmd   *cmd;
    t_redir *redir;
    int     i;

    cmd_node = cmds;
    i = 1;
    while (cmd_node)
    {
        cmd = (t_cmd *)cmd_node->content;
        printf("=== CMD %d ===\n", i++);
        arg_node = cmd->argv_list;
        while (arg_node)
        {
            printf("  ARG: %s\n", (char *)arg_node->content);
            arg_node = arg_node->next;
        }
        redir_node = cmd->redirections;
        while (redir_node)
        {
            redir = (t_redir *)redir_node->content;
            printf("  REDIR: type=%d target=%s\n", redir->type, redir->target);
            redir_node = redir_node->next;
        }
        cmd_node = cmd_node->next;
    }
}