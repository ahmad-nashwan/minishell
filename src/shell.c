<<<<<<< HEAD
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
    shell->env_vars = copy_env(envp);
    if (!shell->env_vars)
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
			rc = parse(shell);
		}
		if (rc == OK)
		{
			//print_cmds(shell->cmds);
			excute_cmds(shell);
		}
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
		input = readline("minishell$ ");
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
	printf("exit\n");
	reset_shell(shell);
	free_env(shell->env_vars);
	rl_clear_history();
	return (shell->exit_status);
}
=======
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
    shell->env_vars = copy_env(envp);
    if (!shell->env_vars)
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
			rc = parse(shell);
		}
    }
    free_t_string(line);
    return rc;
}

int	start_shell(t_shell *shell)
{
	char		*input;

	while (shell->should_exit != 1)
	{
		reset_shell(shell);
		input = readline("minishell$ ");
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
	printf("exit\n");
	reset_shell(shell);
	free_env(shell->env_vars);
	rl_clear_history();
	return (shell->exit_status);
}
>>>>>>> 2beb06267a6ee848002dea1489082cc7719a52a4
