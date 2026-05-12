# include "../../inc/minishell.h"

static int  new_line_flags(char **args)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while (args[i])
    {
        j = 0;
        if (args[i][j] == '-')
        {
            j++;
            if (args[i][j] != 'n')
                break;
            while (args[i][j] == 'n')
                j++;
            if (args[i][j] != '\0')
                break;
        }
        else
            break;
        i++;
    }
    return (i);
}

t_code  echo(char **args, int fd_out)
{
    int i;
    int new_line;

    if (!args)
        return (INTERNAL_ERROR);
    new_line = 1;
    i = new_line_flags(args);
    if (i > 1)
        new_line = 0;
    while (args[i])
    {
        ft_putstr_fd(args[i], fd_out);
        if (args[i + 1])
            ft_putstr_fd(" ", fd_out);
        i++;
    }
     if (new_line)
        ft_putstr_fd("\n", fd_out);
    return (OK);
}
