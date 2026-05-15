#include "../../inc/minishell.h"

static int	check_overflow(long result, int digit, int sign)
{
	if (sign == 1)
	{
		if (result > (LONG_MAX - digit) / 10)
			return (0);
	}
	else
	{
		if (-result < (LONG_MIN + digit) / 10)
			return (0);
	}
	return (1);
}

int	safe_atol(const char *str, long *out)
{
	long i;
	long sign;
	long result;
	int digit;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (!check_overflow(result, digit, sign))
			return (0);
		result = result * 10 + digit;
		i++;
	}
	*out = result * sign;
	return (1);
}