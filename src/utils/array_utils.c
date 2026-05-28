/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 20:56:25 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 20:56:46 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_string_array(t_list *list)
{
	int		size;
	char	**arr;
	int		i;

	if (!list)
		return (NULL);
	size = ft_lstsize(list);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size && list)
	{
		arr[i] = ft_strdup((char *)list->content);
		if (!arr[i])
		{
			free_array(arr, i); // Assuming this frees up to 'i' properly
			return (NULL);
		}
		i++;
		list = list->next;
	}
	arr[i] = NULL;
	return (arr);
}

char	**copy_env(char **envp)
{
	int		var;
	int		i;
	char	**env;

	var = 0;
	while (envp[var])
		var++;
	env = malloc(sizeof(char *) * (var + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (i < var)
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			while (i > 0)
				free(env[--i]);
			free(env);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	free_split(char **words)
{
	size_t	i;

	i = 0;
	if (!words)
		return ;
	while (words[i])
		free(words[i++]);
	free(words);
}

void	free_strings_array(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}