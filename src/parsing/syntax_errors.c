# include "../../inc/minishell.h"

t_code report_syntax_error(char *bad_token)
{
    ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
    if (bad_token)
        ft_putstr_fd(bad_token, 2);
    else
        ft_putstr_fd("newline", 2);
    ft_putendl_fd("'", 2);
    return (SYNTAX_ERROR);
}

t_code parse_error(t_shell* shell, t_cmd *cmd, t_list **cmd_list, t_code error)
{
	if (cmd)
		cmd_free(cmd);
	if (error == INTERNAL_ERROR)
		report_error(shell, error, "Internal error. Exitting.");
	else if (error == SYNTAX_ERROR)
		report_error(shell, error, NULL);
    cmd_list_clear(cmd_list);
    return (error);
}