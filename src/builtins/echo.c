#include "../../inc/minishell.h"

static void	skip_new_line_flags(t_list **args, int *new_line)
{
	char	*str;
	int		i;

	while (*args)
	{
		i = 0;
		str = (char *) (*args)->content;
		if (str[i] == '-')
		{
			i++;
			if (str[i] != 'n')
				break ;
			while (str[i] == 'n')
				i++;
			if (str[i] != '\0')
				break ;
			*new_line = 0;
		}
		else
			break ;
		(*args) = (*args)->next;
	}
}

void  echo(t_shell *shell, t_list *args)
{
    int     new_line;
    char    *str;

    if (!args)
    {
        report_error(shell, INTERNAL_ERROR, "Invalid pointer");
        return ;
    }
    args = args->next;
    if (!args)
        ft_putstr_fd("\n", STDOUT_FILENO);
    new_line = 1;
    skip_new_line_flags(&args, &new_line);
    while (args)
    {
        str = (char *)args->content;
        ft_putstr_fd(str, STDOUT_FILENO);
        if (args->next)
            ft_putstr_fd(" ", STDOUT_FILENO);
        args = args->next;
    }
    if (new_line)
        ft_putstr_fd("\n", STDOUT_FILENO);
}
