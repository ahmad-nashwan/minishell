/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:14:48 by anashwan          #+#    #+#             */
/*   Updated: 2025/09/10 19:59:15 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
1. Count strings [OK]
2. Allocate for the array [REVIEW]
3. Calculate the length of the string until the delimeter [OK]
4. Allocate for the string
5. Fill the string and null-terminate it
6. Add the string to the array
7. Error handling
*/

static int	count_strings(const char *s, char c)
{
	int	strings;
	int	i;

	strings = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			strings++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (strings);
}

static int	get_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static char	*create_string(const char *s, char c)
{
	int		len;
	int		i;
	char	*str;

	len = get_len(s, c);
	str = malloc(len + 1);
	i = 0;
	if (!str)
		return (NULL);
	while (s[i] && i < len && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

static void	*free_split(char **list, int elements)
{
	int	i;

	i = 0;
	while (i < elements)
	{
		free(list[i]);
		i++;
	}
	free(list);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	int		l;

	if (!s)
		return (NULL);
	list = malloc((count_strings(s, c) + 1) * sizeof(char *));
	if (!list)
		return (NULL);
	l = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			list[l++] = create_string(s, c);
			if (!list[l - 1])
				return (free_split(list, l));
			while (*s && *s != c)
				s++;
		}
	}
	list[l] = NULL;
	return (list);
}
