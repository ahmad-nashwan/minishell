#include "../../../inc/minishell.h"


void	export(t_shell *shell, t_list *args)
{
	t_code rc;

	if (!shell || !args)
	{
		report_error(shell, INTERNAL_ERROR, "Invalid pointer");
		return ;
	}
	if (!args->next)
	{
		rc = export_print(shell->env_list);
		if (rc == INTERNAL_ERROR)
		{
			report_error(shell, INTERNAL_ERROR, "Malloc Failure");
			return ;
		}
	}
	else
	{
		rc = export_variables(&shell->env_list, args + 1);
		if (rc == INTERNAL_ERROR)
		{
			report_error(shell, INTERNAL_ERROR, "Malloc Failure");
			return ;
		}
		else if (rc == ERR)
			shell->exit_status = 1;
		else
			shell->exit_status = 0;
	}
}
