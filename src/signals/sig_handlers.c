# include "../../inc/minishell.h"

void    sigint_hdoc_handler(int sig)
{
    (void) sig;
    g_signal = 130;
    write(STDOUT_FILENO, "\n", 1);
}

void    sigint_interactive_handler(int sig)
{
    (void)sig;
    g_signal = 130;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}