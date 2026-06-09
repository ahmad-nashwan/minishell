/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:40:31 by anashwan          #+#    #+#             */
/*   Updated: 2026/06/07 19:31:07 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_code	process_cmd(t_shell *shell, t_list *cmd_node, int *in_fd,
		pid_t *pid)
{
	int	fd[2];

	if (cmd_node->next && pipe(fd) != 0)
		return (INTERNAL_ERROR);
	*pid = fork();
	if (*pid == -1)
		return (INTERNAL_ERROR);
	if (*pid == 0)
	{
		sig_set_child();
		if (cmd_node->next)
			run_child(shell, (t_cmd *)cmd_node->content, *in_fd, fd);
		else
			run_child(shell, (t_cmd *)cmd_node->content, *in_fd, NULL);
		exit_child(shell, shell->exit_status);
	}
	if (*in_fd != -1 && *in_fd != STDIN_FILENO)
		close(*in_fd);
	if (cmd_node->next)
	{
		close(fd[1]);
		*in_fd = fd[0];
	}
	return (OK);
}

static void	wait_for_children(t_shell *shell, int len)
{
	int		i;
	int		state;
	pid_t	pid;

	i = 0;
	while (i < len)
	{
		pid = waitpid(-1, &state, 0);
		if (pid == shell->pids[len - 1])
		{
			if (WIFEXITED(state))
				shell->exit_status = WEXITSTATUS(state);
			else if (WIFSIGNALED(state))
			{
				shell->exit_status = 128 + WTERMSIG(state);
				if (WTERMSIG(state) == SIGINT)
					ft_putstr_fd("\n", STDOUT_FILENO);
				else if (WTERMSIG(state) == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			}
		}
		i++;
	}
}

static void	pipeline_cleanup(t_shell *shell, int len)
{
	wait_for_children(shell, len);
	close_hdoc_fds(shell->cmds);
	if (shell->pids)
		free(shell->pids);
	shell->pids = NULL;
}

static t_code	init_pipeline(t_shell *shell, int *i, int *in_fd, t_list **node)
{
	shell->pids = malloc(sizeof(pid_t) * ft_lstsize(shell->cmds));
	if (!shell->pids)
	{
		report_error(shell, INTERNAL_ERROR, "Malloc Error");
		return (INTERNAL_ERROR);
	}
	*i = 0;
	*in_fd = -1;
	*node = shell->cmds;
	sig_set_execution();
	return (OK);
}

void	process_pipeline(t_shell *shell)
{
	int		i;
	int		input_fd;
	t_list	*node;

	if (init_pipeline(shell, &i, &input_fd, &node) != OK)
		return ;
	while (!shell->should_exit && node)
	{
		if (process_cmd(shell, node, &input_fd, &shell->pids[i]) != OK)
		{
			if (input_fd != -1)
				close(input_fd);
			report_error(shell, INTERNAL_ERROR, "Internal error.");
			break ;
		}
		node = node->next;
		i++;
	}
	pipeline_cleanup(shell, i);
}
