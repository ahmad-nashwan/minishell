#include "../../inc/minishell.h"

t_code excute_cmds(t_shell *shell)
{
	t_list	*cmd_node;
	t_cmd	*cmd;
	char	*cmd_name;

	cmd_node = shell->cmds;
	while (cmd_node)
	{
		cmd = (t_cmd *) cmd_node->content;
		if (cmd->argv_list)
		{
			cmd_name = (char *) cmd->argv_list->content;
			if (ft_strncmp(cmd_name, "env", 3) == 0)
			{
				env(*shell);
				return OK;
			}
			else if (ft_strncmp(cmd_name, "pwd", 3) == 0)
			{
				pwd(STDOUT_FILENO);
				return OK;
			}
			else
				excuter(shell);
		}
		cmd_node = cmd_node->next;
	}
	return OK;
}

