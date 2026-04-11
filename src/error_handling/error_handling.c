# include "../../inc/minishell.h"

void	error_report(char *error)
{
	perror(error);
	exit(1);
}