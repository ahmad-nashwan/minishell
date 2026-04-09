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


t_token *create_token(char *lexeme, token_type type);
void	add_token(t_token **tokens, char *lexeme, token_type type);

// Lexer & Scanners
t_list	*start_lexer(t_string *line);
int scan_word(t_token **tokens, t_string *line);
int	scan_redirection(t_token **tokens, t_string *line);
int	scan_pipe(t_token **tokens, t_string *line);

// t_string Functions
char	advance(t_string *line);
char	peek(t_string *line);
t_string *init_line(char	*str);
char *realloc_string(t_string *word);
