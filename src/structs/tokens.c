#include "../../inc/minishell.h"

t_token *create_token(char *lexeme, token_type type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->lexeme = lexeme;
	token->type = type;
	return (token);
}

void	add_token(t_token **tokens, char *lexeme, token_type type)
{
	t_token *token;

	token = create_token(lexeme, type);
	if (token == NULL)
		error_exit("Malloc Failure");
	ft_lstadd_back(tokens, ft_lstnew(create_token(lexeme, type)));
}

void	free_token(void *ptr)
{
	t_token *token;

	token = (t_token *)ptr;
	if (!token)
		return ;
	if (token->lexeme)
		free(token->lexeme);
	free(token);
}

void	clear_tokens(t_list **tokens)
{
	t_list *node;
	t_token *token;
	t_list *next;

	if (*tokens == NULL)
		return ;
	node = *tokens;
	while (node)
	{
		next = node->next;
		ft_lstdelone(node, free_token);
		node = next;
	}
}
