/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:37:13 by anashwan          #+#    #+#             */
/*   Updated: 2025/09/11 12:37:48 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	size;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	j = 0;
	size = ft_strlen(little);
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while (little[j] && big[(i + j)] == little[j] && (i + j) < len)
			j++;
		if (j == size)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
