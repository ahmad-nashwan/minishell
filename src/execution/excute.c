#include "../../inc/minishell.h"

void excute(t_list *cmds)
{
	t_list  *cmd_node;
    t_list  *arg_node;
    t_cmd   *cmd;
	char *path;
	char **args;
	char **env;

	env = NULL;
	cmd_node = cmds;
	while (cmd_node)
    {
        cmd = (t_cmd *)cmd_node->content;
        arg_node = cmd->argv_list;
		int count = 0;
		while (arg_node)
		{
    		count++;
    		arg_node = arg_node->next;
		}
		args = malloc(sizeof(char *) * (count + 1));
		int j = 0;
		arg_node = cmd->argv_list;
		while (arg_node)
		{
    		args[j++] = (char *)arg_node->content;
    		arg_node = arg_node->next;
		}
		args[j] = NULL;
		path = ft_strjoin("/usr/bin/",args[0]);
		execve(path, args, env);
		free(path);
		free(args);
        cmd_node = cmd_node->next;
    }
}

