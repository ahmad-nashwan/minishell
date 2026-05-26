/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:20:11 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:20:12 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env_var	*new_env_var(const char *key, const char *value)
{
	t_env_var	*var;

	var = malloc(sizeof(t_env_var));
	if (!var)
		return (NULL);
	var->key = ft_strdup(key);
	if (!var->key)
	{
		free(var);
		return (NULL);
	}
	var->value = NULL;
	if (value)
	{
		var->value = ft_strdup(value);
		if (!var->value)
		{
			free(var->key);
			free(var);
			return (NULL);
		}
	}
	return (var);
}

t_env_var	*find_env_var(t_list *env_list, const char *key)
{
	t_list		*node;
	t_env_var	*var;

	if (!env_list || !key)
		return (NULL);
	node = env_list;
	while (node)
	{
		var = (t_env_var *)node->content;
		if (ft_strncmp(var->key, key, ft_strlen(key) + 1) == 0)
			return (var);
		node = node->next;
	}
	return (NULL);
}

t_code	update_env_value(t_env_var *env, const char *value)
{
	char	*new_val;

	if (!env)
		return (INTERNAL_ERROR);
	if (!value)
		return (OK);
	new_val = ft_strdup(value);
	if (!new_val)
		return (INTERNAL_ERROR);
	if (env->value)
		free(env->value);
	env->value = new_val;
	return (OK);
}

t_code	add_env_var(t_list **env_list, t_env_var *var)
{
	t_list	*node;

	if (!env_list || !var)
		return (INTERNAL_ERROR);
	node = ft_lstnew(var);
	if (!node)
		return (INTERNAL_ERROR);
	ft_lstadd_back(env_list, node);
	return (OK);
}

void	free_env_var(void *content)
{
	t_env_var	*var;

	if (!content)
		return ;
	var = (t_env_var *)content;
	if (var->key)
		free(var->key);
	if (var->value)
		free(var->value);
	free(var);
}
