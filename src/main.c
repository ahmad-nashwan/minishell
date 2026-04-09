# include "../inc/minishell.h"

int main(int argc, char **argv)
{
	if (argc > 1)
		return (1);
	meowshell();
	return (0);
}