# include "../inc/minishell.h"

int main(int argc, char **argv)
{
	if (argc > 1)
		return (1);
	(void)argv;
	meowshell();
	return (0);
}