# include "../../inc/minishell.h"


static t_code parse_redir(t_cmd *cmd, t_token *redir, t_token *target)
{
    t_redir *redirection;

    if (!cmd || !redir || !target)
        return (INTERNAL_ERROR);
    redirection = redir_create(redir->type, target->lexeme);
    if (!redirection)
        return (INTERNAL_ERROR);
    return (cmd_add_redir(cmd, redirection));
}

static t_code build_cmd(t_cmd *cmd, t_list **node)
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
                return (SYNTAX_ERROR);
            next_token = (t_token *)(*node)->next->content;
            if (next_token->type != WORD)
                return (SYNTAX_ERROR);
            if (parse_redir(cmd, token, next_token)) 
                return (INTERNAL_ERROR);
            (*node) = (*node)->next->next;; // consuming the redirection token, safe because we have a check before
        }
        else
        {
            if (cmd_add_arg(cmd, token->lexeme) != OK)
				return (INTERNAL_ERROR);
            (*node) =(*node)->next; // consume arg
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
            return (SYNTAX_ERROR); // Syntax error, pipe at the end
        next_token = (t_token *)n->next->content;
        if (next_token->type == END || next_token->type == PIPE)
            return (SYNTAX_ERROR); // Syntax error
        (*node) = (*node)->next; // consume pipe
    }
    return (OK);
}

static t_code parse_error(t_shell* shell, t_cmd *cmd, t_list **cmd_list, t_code error)
{
	if (cmd)
		cmd_free(cmd);
	if (error == INTERNAL_ERROR)
		report_error(shell, error, "Internal error. Exitting.");
	else if (error == SYNTAX_ERROR)
		report_error(shell, error, "Syntax Error");
    cmd_list_clear(cmd_list);
    return (error);
}

t_code	parse(t_shell *shell)
{
    t_list  *node; // for traversal over the tokens list
    t_cmd   *cmd;
    t_token *token;
    t_code	rc;

    node = shell->tokens;
    while (node)
    {
        token = (t_token *) node->content;
        if (token->type == END)
            break;
        if (token->type == PIPE)
            return (parse_error(shell, NULL, &shell->cmds, SYNTAX_ERROR));
        cmd = cmd_create();
        if (!cmd)
            return (parse_error(shell, NULL, &shell->cmds, INTERNAL_ERROR));
		rc = build_cmd(cmd, &node);
        if (rc != OK)
            return (parse_error(shell, cmd, &shell->cmds, rc));
		rc = consume_pipe(&node);
        if (rc != OK)
            return (parse_error(shell, cmd, &shell->cmds, rc));
		rc = cmd_list_add(&shell->cmds, cmd);
        if (rc != OK)
            return (parse_error(shell, cmd, &shell->cmds, rc));
    }
    return (OK);
}
