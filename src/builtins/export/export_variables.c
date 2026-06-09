/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:41:21 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:45:28 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !(*str == '_' || ft_isalpha(*str)))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static t_code	export_without_value(t_list **env_list, char *arg)
{
	t_env_var	*var;

	if (find_env_var(*env_list, arg))
		return (OK);
	var = new_env_var(arg, NULL);
	if (!var)
		return (ERR);
	return (add_env_var(env_list, var));
}

static t_code	export_with_value(t_list **env_list, char *arg, char *eq)
{
	char		*key;
	t_env_var	*var;

	key = ft_substr(arg, 0, eq - arg);
	if (!key)
		return (ERR);
	var = find_env_var(*env_list, key);
	if (var)
	{
		free(key);
		return (update_env_value(var, eq + 1));
	}
	var = new_env_var(key, eq + 1);
	free(key);
	if (!var)
		return (ERR);
	return (add_env_var(env_list, var));
}

static t_code	process_export(t_list **env_list, char *arg)
{
	char	*eq;
	t_code	rc;

	eq = ft_strchr(arg, '=');
	if (!eq)
		rc = export_without_value(env_list, arg);
	else
		rc = export_with_value(env_list, arg, eq);
	return (rc);
}

t_code	export_variables(t_list **env_list, t_list *args)
{
	t_code	final_status;

	final_status = OK;
	args = args->next;
	while (args)
	{
		if (!is_valid_identifier((char *)args->content))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd((char *)args->content, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			final_status = ERR;
		}
		else
		{
			if (process_export(env_list, (char *)args->content) != OK)
			{
				final_status = INTERNAL_ERROR;
				break ;
			}
		}
		args = args->next;
	}
	return (final_status);
}
