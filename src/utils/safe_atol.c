/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_atol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:18:22 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:18:23 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_overflow(unsigned long result, int digit, int sign)
{
	unsigned long	max;

	if (sign == 1)
		max = LONG_MAX;
	else
		max = (unsigned long)LONG_MAX + 1;
	if (result > (max - digit) / 10)
		return (0);
	return (1);
}

static void pre_process_str(const char *str, int *i,int *sign)
{
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32)
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

int	safe_atol(const char *str, long *out)
{
	int			i;
	int			sign;
	unsigned long	result;
	int				digit;

	i = 0;
	sign = 1;
	result = 0;
	pre_process_str(str, &i, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (!check_overflow(result, digit, sign))
			return (0);
		result = result * 10 + digit;
		i++;
	}
	if (sign == -1 && result == (unsigned long)LONG_MAX + 1)
		*out = LONG_MIN;
	else
		*out = (long)result * sign;
	return (1);
}
