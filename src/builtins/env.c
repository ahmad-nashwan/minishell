/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:41:07 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:41:08 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_env(t_list *env_list)
{
	t_env_var	*var;

	while (env_list)
	{
		var = (t_env_var *)env_list->content;
		if (var->value != NULL)
		{
			ft_putstr_fd(var->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(var->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		env_list = env_list->next;
	}
}

void	env(t_shell *shell, t_list *args)
{
	if (!args)
	{
		report_error(shell, INTERNAL_ERROR, "Invalid pointer");
		return ;
	}
	if (args->next != NULL)
	{
		ft_putstr_fd("env: '", STDERR_FILENO);
		ft_putstr_fd((char *)args->next->content, STDERR_FILENO);
		ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
		shell->exit_status = 127;
		return ;
	}
	print_env(shell->env_list);
	shell->exit_status = 0;
}
