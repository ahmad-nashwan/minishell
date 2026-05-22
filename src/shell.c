# include "../inc/minishell.h"

void    init_shell(t_shell *shell, char **envp)
{
    shell->env_list = NULL;
    if (envp && *envp)
    {
        shell->env_list = init_env_list(envp);
        if (!shell->env_list)
            error_exit("Malloc failure.");
    }
    shell->cwd = NULL;
    shell->tokens = NULL;
    shell->cmds = NULL;
    shell->exit_status = 0;
    shell->error_type = NONE;
    shell->should_exit = 0;
}

void	reset_shell(t_shell *shell)
{
	if (shell->tokens)
		clear_tokens(&shell->tokens);
	shell->tokens = NULL;
	if (shell->cmds)
		cmd_list_clear(&shell->cmds);
	shell->cmds = NULL;
}

void process_input(t_shell *shell, char *input)
{
    t_string	*line;
	t_code		rc;

	rc = OK;
    line = init_string(ft_strdup(input));
    if (!line)
	{
        report_error(shell, INTERNAL_ERROR, "Malloc Failure");
		return ;
	}
    if (*line->str)
    {
        add_history(line->str);
        if (rc == OK)
			rc = tokenizer(shell, line);
		if (rc == OK)
			rc = parse(shell);
		if (rc == OK)
			process_commands(shell);
    }
    free_t_string(line);
}

int	start_shell(t_shell *shell)
{
	char	*input;

	while (shell->should_exit != 1)
	{
		reset_shell(shell);
		input = readline("minishell$ ");
		if (!input)
			break;
		process_input(shell, input);
		free(input);
	}
	if (!input)
    	ft_putstr_fd("exit\n", STDERR_FILENO);
	reset_shell(shell);
	ft_lstclear(&shell->env_list, free_env_var);
	rl_clear_history();
	return (shell->exit_status);
}