/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:41:08 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:41:09 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	exit_non_numerial(t_shell *shell, char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	report_error(shell, ERR, NULL);
	shell->exit_status = 2;
	shell->should_exit = 1;
}

static void	exit_many_args(t_shell *shell)
{
	shell->exit_status = 1;
	report_error(shell, ERR, "exit: too many arguments");
}

void	shell_exit(t_shell *shell, t_list *args)
{
	long	code;
	char	*str;

	if (!args)
	{
		report_error(shell, INTERNAL_ERROR, "Invalid pointer");
		return ;
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!args->next)
	{
		shell->should_exit = 1;
		return ;
	}
	str = (char *)args->next->content;
	if (!is_number(str) || !safe_atol(str, &code))
		exit_non_numerial(shell, str);
	if (args->next->next)
	{
		exit_many_args(shell);
	}
	shell->exit_status = (unsigned char)code;
	shell->should_exit = 1;
}
