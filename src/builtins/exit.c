# include "../../inc/minishell.h"

static void exit_non_numerial(t_shell *shell)
{
    report_error(shell, ERR, "exit: numeric argument required");
    shell->exit_status = 2;
    shell->should_exit = 1;
}

static void exit_many_args(t_shell *shell)
{
    shell->exit_status = 1;
    report_error(shell, ERR, "exit: too many arguments");
} 

void  shell_exit(t_shell *shell, char **args)
{
    long    code;

    ft_putstr_fd("exit\n", 2);
    if (!args[1])
    {
        shell->should_exit = 1;
        return (ERR);
    }
    if (!is_number(args[1]) || !safe_atol(args[1], &code))
    {
        exit_non_numerial(shell);
        return (ERR);
    }
    if (args[2])
    {
        exit_many_args(shell);
        return ;
    }
    shell->exit_status = (unsigned char)code;
    shell->should_exit = 1;
    return (OK);
}
