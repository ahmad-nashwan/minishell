#include "../../../inc/minishell.h"


void	export(t_shell *shell, t_list *args)
{
	if (!shell || !args)
	{
		report_error(shell, INTERNAL_ERROR, "Invalid pointer");
		return ;
	}
	if (!args->next)
	{
		if (export_print(shell->env_list) == ERR)
			report_error(shell, INTERNAL_ERROR, "Malloc Failure");
	}
	else
	{
		if (export_variables(&shell->env_list, args->next) == ERR)
			report_error(shell, INTERNAL_ERROR, "Malloc Failure");
	}
}