/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_single_builtin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:40:35 by anashwan          #+#    #+#             */
/*   Updated: 2026/06/10 13:38:00 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_saved_fds(int saved_stdout, int saved_stdin)
{
	if (saved_stdout != -1)
		close(saved_stdout);
	if (saved_stdin != -1)
		close(saved_stdin);
}

static void	restore_fds(int saved_stdout, int saved_stdin, t_shell *shell)
{
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		report_error(shell, INTERNAL_ERROR, NULL);
	}
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		report_error(shell, INTERNAL_ERROR, NULL);
	}
}

void	process_single_builtin(t_shell *shell, t_cmd *cmd)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdout == -1 || saved_stdin == -1)
	{
		report_error(shell, INTERNAL_ERROR, "dup failed");
		close_saved_fds(saved_stdout, saved_stdin);
		return ;
	}
	if (handle_redirections(cmd) == ERR)
	{
		shell->exit_status = 1;
		restore_fds(saved_stdout, saved_stdin, shell);
		close_saved_fds(saved_stdout, saved_stdin);
		return ;
	}
	run_builtin(shell, cmd);
	restore_fds(saved_stdout, saved_stdin, shell);
	close_saved_fds(saved_stdout, saved_stdin);
}
