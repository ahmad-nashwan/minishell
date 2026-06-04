/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:08:21 by anashwan          #+#    #+#             */
/*   Updated: 2025/09/09 19:00:37 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	size_t	j;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(s1);
	if (len == 0)
		return (ft_strdup(""));
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (len && len >= i && ft_strchr(set, s1[len]))
		len--;
	trimmed = malloc((len - i + 2));
	if (!trimmed)
		return (NULL);
	while (i <= len)
		trimmed[j++] = s1[i++];
	trimmed[j] = '\0';
	return (trimmed);
}
