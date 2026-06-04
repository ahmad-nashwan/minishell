/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:10:12 by anashwan          #+#    #+#             */
/*   Updated: 2025/09/11 12:37:56 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = ft_strlen(str);
	c = (unsigned char)c;
	if (c == '\0' && str[i] == '\0')
		return (str + i);
	while (i--)
	{
		if (str[i] == c)
			return (str + i);
	}
	return (NULL);
}
