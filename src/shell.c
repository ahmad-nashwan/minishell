# include "../inc/minishell.h"

int	meowshell()
{
	t_string	line;

	line.str = readline("meowshell> ");
	line.index = 0;
	line.len = ft_strlen(line.str);
	while (line.str)
	{
		if (ft_strlen(line.str) != 0)
		{
			add_history(line.str);
			start_lexer(&line);
		}
		free(line.str);
		line.str = readline("meowshell> ");
	}
}