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

t_code	add_token(t_list **tokens, char *lexeme, t_type type)
{
	t_token *token;
	t_list 	*new_node;
	if (!tokens)
		return (INTERNAL_ERROR);
	token = create_token(lexeme, type); // MEMORY_CHECK[OK]
	if (token == NULL)
		return (INTERNAL_ERROR);
	new_node = ft_lstnew(token);  // MEMORY_CHECK[OK]
	if (!new_node)
	{
		free(token);
		return (INTERNAL_ERROR);
	}
	ft_lstadd_back(tokens, new_node);
	return (OK);
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