/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:13:46 by anashwan          #+#    #+#             */
/*   Updated: 2025/09/11 11:09:28 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*fill_string(long n, int size, char *s)
{
	int	temp;

	if (n == 0)
		s[size] = '0';
	while (n)
	{
		temp = n % 10;
		s[size--] = temp + '0';
		n /= 10;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		negative;
	int		size;
	long	e;

	e = n;
	negative = 0;
	size = count_digits(e);
	if (e < 0)
	{
		e *= -1;
		negative = 1;
		size++;
	}
	s = malloc(size + 1);
	if (!s)
		return (NULL);
	s[size--] = '\0';
	fill_string(e, size, s);
	if (negative)
		s[0] = '-';
	return (s);
}
