#include "../../inc/minishell.h"

static int  check_overflow(unsigned long result, int digit, int sign)
{
    unsigned long max;

    if (sign == 1)
        max = LONG_MAX;
    else
        max = (unsigned long)LONG_MAX + 1;
    if (result > (max - digit) / 10)
        return (0);
    return (1);
}

int	safe_atol(const char *str, long *out)
{
	long i;
	long sign;
	unsigned long result;
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
	if (sign == -1 && result == (unsigned long)LONG_MAX + 1)
        *out = LONG_MIN;
    else
        *out = (long)result * sign;
	return (1);
}
