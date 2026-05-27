/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:41:12 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:46:19 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_shell *shell)
{
	char	*env_pwd;
	char	*wd;

	env_pwd = get_env_value(shell->env_list, "PWD");
	if (env_pwd)
	{
		ft_putendl_fd(env_pwd, STDOUT_FILENO);
		shell->exit_status = 0;
		return ;
	}
	wd = getcwd(NULL, 0);
	if (wd)
	{
		ft_putendl_fd(wd, STDOUT_FILENO);
		free(wd);
		shell->exit_status = 0;
		return ;
	}
	perror("minishell: pwd");
	shell->exit_status = 1;
}
