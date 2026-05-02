# include "../../inc/minishell.h"


static int parse_redir(t_cmd *cmd, t_token *redir, t_token *target)
{
    t_redir *redirection;

    if (!cmd || !redir || !target)
        return (1);
    if (target->type != WORD)
        return (1);
    redirection = redir_create(redir->type, target->lexeme);
    if (!redirection)
        return (1);
    return (cmd_add_redir(cmd, redirection));
}

static int build_cmd(t_cmd *cmd, t_list **node)
{
    t_token *token;
    t_token *next_token;

    while (*node)
    {
        token = (t_token *)(*node)->content;
        if (token->type == PIPE || token->type == END)
            return (0);
        if (token->type != WORD)
        {
            if (!(*node)->next)
                return (1);
            next_token = (t_token *)(*node)->next->content;
            if (parse_redir(cmd, token, next_token)) // will return 1 if it's a pipe
                return (1);
            (*node) = (*node)->next; // consuming the redirection token, safe because we have a check before
            (*node) = (*node)->next; // consume target
        }
        else
        {
            cmd_add_arg(cmd, token->lexeme);
            (*node) =(*node)->next; // consume arg
        }
    }
    return (0);
}

static int  consume_pipe(t_list **node)
{
    t_token *token;
    t_token *next_token;
    t_list *n;

    n = (*node);
    token = (t_token *)n->content;
    if (token->type == END)
        return (0); // Do nothing
    if (token->type == PIPE) // real work
    {
        if (!n->next)
            return (1); // Syntax error, pipe at the end
        next_token = (t_token *)n->next->content;
        if (next_token->type == END || next_token->type == PIPE)
            return (1); // Syntax error
        (*node) = (*node)->next; // consume pipe
    }
    return (0);
}

static int syntax_error(t_cmd *cmd, t_list **cmd_list)
{
    if (cmd)
        cmd_free(cmd);
    ft_putendl_fd("meowshell: Syntax error", 2);
    cmd_list_clear(cmd_list);
    return (1);
}

int	parse(t_shell *shell)
{
    t_list  *node; // for traversal over the tokens list
    t_cmd   *cmd;
    t_token *token;

    node = shell->tokens;
    while (node)
    {
        token = (t_token *) node->content;
        if (token->type == END)
            break;
        if (token->type == PIPE)
            return (syntax_error(NULL, &shell->cmds));
        cmd = cmd_create();
        if (!cmd)
            return (syntax_error(NULL, &shell->cmds));
        if (build_cmd(cmd, &node))
            return (syntax_error(cmd, &shell->cmds));
        if (consume_pipe(&node))
            return (syntax_error(cmd, &shell->cmds));
        if (cmd_list_add(&shell->cmds, cmd))
            return (syntax_error(cmd, &shell->cmds));
    }
    return (0);
}
