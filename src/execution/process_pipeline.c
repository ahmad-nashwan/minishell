/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:40:31 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/27 02:20:21 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static t_code	pipeline_error(t_shell *shell, t_code e, char *msg)
{
	report_error(shell, e, msg);
	return (ERR);
}

static t_code	process_cmd(t_shell *shell, t_list *cmd_node, int *in_fd, pid_t *pid)
{
	int		fd[2];

	if (cmd_node->next && pipe(fd) != 0)
		return (pipeline_error(shell, INTERNAL_ERROR, "Pipe failure"));
	*pid = fork();
	if (*pid == -1)
		return (pipeline_error(shell, INTERNAL_ERROR, "Fork failed"));
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

static void	wait_for_children(t_shell *shell, pid_t *pids, int len)
{
	int	i;
	int	state;

	i = 0;
	while (i < len)
	{
		waitpid(pids[i], &state, 0);
		if (i == len - 1)
		{
			if (WIFEXITED(state))
				shell->exit_status = WEXITSTATUS(state);
			else if (WIFSIGNALED(state))
			{
				shell->exit_status = 128 + WTERMSIG(state);
				if (WTERMSIG(state) == SIGINT)
					ft_putstr_fd("\n", STDOUT_FILENO);
				else if (WTERMSIG(state) == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
			}
		}
		i++;
	}
}

t_code	process_pipeline(t_shell *shell)
{
	t_list	*node;
	pid_t	*pids;
	int		i;
	int		input_fd;

	pids = malloc(sizeof(pid_t) * ft_lstsize(shell->cmds));
	if (!pids)
		return (pipeline_error(shell, INTERNAL_ERROR, "Malloc failed"));
	i = 0;
	input_fd = -1;
	node = shell->cmds;
	sig_set_execution();
	while (!shell->should_exit && node)
	{
		if (process_cmd(shell, node, &input_fd, &pids[i]) != OK)
			break ;
		node = node->next;
		i++;
	}
	wait_for_children(shell, pids, i);
	close_hdoc_fds(shell->cmds);
	free(pids);
	return (OK);
}
