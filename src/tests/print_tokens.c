# include "minishell.h"

void	print_tokens(t_list *tokens)
{
	t_list *node;
	t_token *token;

	node = tokens;
	while (node)
	{
		token = (t_token *)node->content;
		if (token->lexeme)
		{
			printf("WORD(%s)", token->lexeme);
		}
		else
		{
			if (token->type == PIPE)
				printf("PIPE");
			else if (token->type == HEREDOC)
				printf("HEREDOC");
			else if (token->type == IN_RED)
				printf("IN_RED");
			else if (token->type == OUT_RED)
				printf("OUT_RED");
			else if (token->type == APPEND)
				printf("APPEND");
			else if (token->type == END)
				printf("END");
		}
		printf(" ");
		node = node->next;
	}
}