# include "../inc/minishell.h"

int	meowshell()
{
	t_string	line;
	t_token *tokens;

	while (1)
	{
		line.str = readline("meowshell> ");
		if (!line.str)
			break;
		if (*line.str)
		{
			add_history(line.str);
			line.index = 0;
			line.len = ft_strlen(line.str);
			tokens = start_lexer(&line);
			print_tokens(tokens);
			clear_tokens(&tokens);
		}
		free(line.str);
	}
	return (0);
}