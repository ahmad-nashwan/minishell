#include "../../inc/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c =='\r')
		return (1);
	return (0);
}
