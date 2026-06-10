/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:40:48 by anashwan          #+#    #+#             */
/*   Updated: 2026/06/10 14:29:42 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static int	error_to_exit_code(t_code e)
{
	if (e == NONE)
		return (0);
	if (e == SYNTAX_ERROR)
		return (2);
	if (e == INTERNAL_ERROR)
		return (1);
	if (e == INTERRUPTED)
		return (130);
	return (1);
}

void	report_error(t_shell *shell, t_code e, char *msg)
{
	shell->error_type = e;
	shell->exit_status = error_to_exit_code(e);
	if (e == INTERNAL_ERROR)
		shell->should_exit = 1;
	if (msg)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
}

void	print_cmd_error(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
}
