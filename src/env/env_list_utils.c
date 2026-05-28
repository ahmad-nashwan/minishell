/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:40:54 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:40:55 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*node_from_env_str(char *env_str)
{
	char		*eq_pos;
	char		*key;
	t_env_var	*var;
	t_list		*node;

	eq_pos = ft_strchr(env_str, '=');
	if (!eq_pos)
		var = new_env_var(env_str, NULL);
	else
	{
		key = ft_substr(env_str, 0, eq_pos - env_str);
		if (!key)
			return (NULL);
		var = new_env_var(key, eq_pos + 1);
		free(key); // MUST FREE OR WE DIE
	}
	if (!var)
		return (NULL);
	node = ft_lstnew(var);
	if (!node)
		free_env_var(var); // ALSO MUST FREE OR WE DIE
	return (node);
}

t_list	*init_env_list(char **envp)
{
	t_list	*env_list;
	t_list	*new_node;
	int		i;

	env_list = NULL;
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_node = node_from_env_str(envp[i]);
		if (!new_node)
		{
			ft_lstclear(&env_list, free_env_var);
			return (NULL);
		}
		ft_lstadd_back(&env_list, new_node);
		i++;
	}
	return (env_list);
}

char	*get_env_value(t_list *env_list, const char *key)
{
	t_env_var	*env_var;
	size_t		key_len;

	if (!env_list || !key)
		return (NULL);
	key_len = ft_strlen(key);
	while (env_list)
	{
		env_var = (t_env_var *)env_list->content;
		if (ft_strncmp(env_var->key, key, key_len) == 0
			&& env_var->key[key_len] == '\0')
		{
			return (env_var->value);
		}
		env_list = env_list->next;
	}
	return (NULL);
}
