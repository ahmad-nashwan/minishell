/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 20:56:10 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/27 03:39:40 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	shell->env_list = NULL;
	if (envp && *envp)
	{
		shell->env_list = init_env_list(envp);
		if (!shell->env_list)
			error_exit("Malloc failure.");
		check_shell_level(shell->env_list);

	}
	
	shell->curr_input = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->exit_status = 0;
	shell->error_type = NONE;
	shell->should_exit = 0;
}

void	reset_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->curr_input)
		free_t_string(shell->curr_input);
	shell->curr_input = NULL;
	if (shell->tokens)
		clear_tokens(&shell->tokens);
	shell->tokens = NULL;
	if (shell->cmds)
		cmd_list_clear(&shell->cmds);
	shell->cmds = NULL;
}

void	free_shell_state(t_shell *shell)
{
	if (!shell)
		return ;
	reset_shell(shell); 
	if (shell->env_list)
		ft_lstclear(&shell->env_list, free_env_var);
	shell->env_list = NULL;
	rl_clear_history(); 
}

void	process_input(t_shell *shell, char *input)
{
	t_code		rc;

	rc = OK;
	shell->curr_input = init_string(input);
	if (!shell->curr_input)
	{
		report_error(shell, INTERNAL_ERROR, "Malloc Failure");
		return ;
	}
	if (*shell->curr_input->str)
	{
		add_history(shell->curr_input->str);
		if (rc == OK)
			rc = tokenizer(shell, shell->curr_input);
		if (rc == OK)
			rc = parse(shell);
		if (rc == OK)
			process_commands(shell);
	}
	free_t_string(shell->curr_input);
	shell->curr_input = NULL;
}

int	start_shell(t_shell *shell)
{
	char *input;

	while (shell->should_exit != 1)
	{
		sig_set_interactive();
		reset_shell(shell);
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (g_signal)
		{
			shell->exit_status = g_signal;
			g_signal = 0;
		}
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
