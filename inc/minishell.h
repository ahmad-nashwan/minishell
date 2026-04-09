# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
# include "../libft/libft.h"

typedef enum s_token_type
{
	WORD, PIPE,
	HEREDOC, OUT_RED, IN_RED, APPEND, 
	INVALID, END
} token_type;

typedef struct s_token 
{
	char *lexeme;
	token_type type;
} t_token;

typedef struct s_string
{
	char 	*str;
	size_t	index;
	size_t	cap;
	size_t	len;
} t_string;


// t_string Functions
char	advance(t_string *line);
char	peek(t_string *line);
t_string *init_line(char	*str);
char *realloc_string(t_string *word);


// t_token Functions
t_token *create_token(char *lexeme, token_type type);
void	add_token(t_list **tokens, char *lexeme, token_type type);
void	free_token(void *ptr);
void	clear_tokens(t_list **tokens);

// Lexer & Scanners
t_list	*start_lexer(t_string *line);
int scan_word(t_list **tokens, t_string *line);
int	scan_redirection(t_list **tokens, t_string *line);
int	scan_pipe(t_list **tokens, t_string *line);

// Helpers
int	ft_isspace(char c);

// Tests
void	print_tokens(t_list *tokens);

int	meowshell();