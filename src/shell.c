# include "../inc/minishell.h"

void	reset_shell(t_shell *shell)
{
	if (shell->tokens)
		clear_tokens(&shell->tokens);
	shell->tokens = NULL;
	if (shell->cmds)
		cmd_list_clear(&shell->cmds);
	shell->cmds = NULL;
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

int	start_shell(t_shell *shell)
{
	t_string	*line;
	shell->tokens = NULL;
	shell->cmds = NULL;
	while (1)
	{
		reset_shell(shell);
		line = init_string(readline("meowshell> "));
		if (!line)
		break;
		if (*line->str)
		{
			add_history(line->str);
			tokenizer(shell, line);
			parse(shell);
			print_cmds(shell->cmds);
			printf("\n");
		}
		free_t_string(line);
	}
	reset_shell(shell);
	free_env(shell->env);
	rl_clear_history();
	return (0);
}
