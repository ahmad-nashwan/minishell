# include "../../inc/minishell.h"

static t_code parse_redir(t_cmd *cmd, t_token *redir, t_token *target)
{
    t_redir *redirection;

    if (!cmd || !redir || !target)
        return (INTERNAL_ERROR);
    redirection = redir_create(redir->type, target->lexeme);
    if (!redirection)
        return (INTERNAL_ERROR);
        
    if (redirection->type == HEREDOC)
    {
        redirection->h_fd = handle_heredoc(redirection->target); 
        if (redirection->h_fd == -1)
        {
            free(redirection->target);
            free(redirection);
            return (INTERNAL_ERROR); 
        }
    }
    return (cmd_add_redir(cmd, redirection));
}

t_code build_cmd(t_cmd *cmd, t_list **node)
{
    t_token *token;
    t_token *next_token;

    while (*node)
    {
        token = (t_token *)(*node)->content;
        if (token->type == PIPE || token->type == END)
            return (OK);
        if (token->type != WORD)
        {
            if (!(*node)->next)
                return (report_syntax_error("newline")); 
            next_token = (t_token *)(*node)->next->content;
            if (next_token->type != WORD)
                return (report_syntax_error(next_token->lexeme));
            if (parse_redir(cmd, token, next_token)) 
                return (INTERNAL_ERROR);
            (*node) = (*node)->next->next; // consuming the redirection token, safe because we have a check before
        }
        else
        {
            if (cmd_add_arg(cmd, token->lexeme) != OK)
				return (INTERNAL_ERROR);
            (*node) =(*node)->next;
        }
    }
    return (OK);
}

static t_code  consume_pipe(t_list **node)
{
    t_token *token;
    t_token *next_token;
    t_list *n;

    n = (*node);
    token = (t_token *)n->content;
    if (token->type == END)
        return (OK); // Do nothing
    if (token->type == PIPE) // real work
    {
        if (!n->next)
            return (report_syntax_error("|")); // Syntax error, pipe at the end
        next_token = (t_token *)n->next->content;
        if (next_token->type == END || next_token->type == PIPE)
            return (report_syntax_error("|")); // Syntax error
        (*node) = (*node)->next; // consume pipe
    }
    return (OK);
}

static t_code process_node(t_shell *shell, t_list **node)
{
    t_cmd   *cmd;
    t_token *token;
    t_code  rc;

    token = (t_token *)(*node)->content;
    if (token->type == PIPE)
    {
        report_syntax_error("|");
        return (parse_error(shell, NULL, &shell->cmds, SYNTAX_ERROR));
    }
    cmd = cmd_create();
    if (!cmd)
        return (parse_error(shell, NULL, &shell->cmds, INTERNAL_ERROR));
    rc = build_cmd(cmd, node);
    if (rc != OK)
        return (parse_error(shell, cmd, &shell->cmds, rc));
    rc = consume_pipe(node);
    if (rc != OK)
        return (parse_error(shell, cmd, &shell->cmds, rc));
    rc = cmd_list_add(&shell->cmds, cmd);
    if (rc != OK)
        return (parse_error(shell, cmd, &shell->cmds, rc));
    return (OK);
}

t_code  parse(t_shell *shell)
{
    t_list  *node; 
    t_token *token;
    t_code  rc;

    node = shell->tokens;
    while (node)
    {
        token = (t_token *) node->content;
        if (token->type == END)
            break;
            
        rc = process_node(shell, &node);
        if (rc != OK)
            return (rc);
    }
    return (OK);
}
