#include "../../inc/minishell.h"

t_token *create_token(char *lexeme, t_type type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->lexeme = lexeme;
	token->type = type;
	return (token);
}

void	add_token(t_list **tokens, char *lexeme, t_type type)
{
	t_token *token;

	token = create_token(lexeme, type);
	if (token == NULL)
		error_exit("Malloc Failure");
	ft_lstadd_back(tokens, ft_lstnew(token));
}

void	free_token(void *ptr)
{
	t_token *token;

	token = (t_token *)ptr;
	if (!token)
		return ;
	free(token->lexeme);
	free(token);
}
void clear_tokens(t_list **tokens)
{
	ft_lstclear(tokens, free_token);
}