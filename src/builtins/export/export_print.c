/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:41:19 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:41:20 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	sort_env_arr(char **arr, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export_line(char *str)
{
	char	*eq;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	eq = ft_strchr(str, '=');
	if (!eq)
	{
		ft_putstr_fd(str, STDOUT_FILENO);
	}
	else
	{
		// Print KEY=
		write(STDOUT_FILENO, str, eq - str + 1);
		// Print "VALUE"
		ft_putstr_fd("\"", STDOUT_FILENO);
		ft_putstr_fd(eq + 1, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

t_code	export_print(t_list *env_list)
{
	char	**env_arr;
	int		i;

	env_arr = env_to_array(env_list);
	if (!env_arr)
		return (INTERNAL_ERROR);
	sort_env_arr(env_arr, ft_lstsize(env_list));
	i = 0;
	while (env_arr[i])
	{
		print_export_line(env_arr[i]);
		i++;
	}
	free_array(env_arr, i);
	free(env_arr);
	return (OK);
}
