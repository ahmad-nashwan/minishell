/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:18:35 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:18:36 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r')
		return (1);
	return (0);
}

int	is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] == ' ' || (arg[i] >= '\t' && arg[i] <= '\r'))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		return (0);
	while (ft_isdigit(arg[i]))
		i++;
	while (arg[i] == ' ' || (arg[i] >= '\t' && arg[i] <= '\r'))
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}