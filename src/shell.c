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


void init_shell(t_shell *shell, char **envp)
{
    shell->env = copy_env(envp);
    if (!shell->env)
        error_exit("Malloc failure.");

    shell->tokens = NULL;
    shell->cmds = NULL;
    shell->exit_status = 0;
    shell->error_type = NONE;
    shell->should_exit = 0;
}

t_code process_input(t_shell *shell, char *input)
{
    t_string *line;
    t_code    rc;

	rc = OK;
    line = init_string(ft_strdup(input));
    if (!line)
        return INTERNAL_ERROR;
    if (*line->str)
    {
        add_history(line->str);
        if (rc == OK)
		{
			rc = tokenizer(shell, line);
		}
		if (rc == OK)
		{	
			print_tokens(shell->tokens);
			printf("\n");
		}
		// if (rc == OK)
        // 	rc = parse(shell);
		// if (rc == OK) // for testing only
		// {
		// 	print_cmds(shell->cmds);
		// 	printf("\n");
		// }
        // if (rc == OK)
        //     rc = execute(shell);
    }
    free_t_string(line);
    return rc;
}

int	start_shell(t_shell *shell)
{
	char		*input;

	while (1)
	{
		reset_shell(shell);
		input = readline("meowshell> ");
		if (!input)
			break;
		if (process_input(shell, input) != OK)
		{
			if (handle_error(shell) != OK)
			{
				free(input);
				break;
			}
		}
		free(input);
	}
	reset_shell(shell);
	free_env(shell->env);
	rl_clear_history();
	return (shell->exit_status);
}
