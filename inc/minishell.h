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


typedef struct s_shell
{
    char    **env;        // environment variables
    int     exit_status;  // for $? expansion
    t_list  *tokens;      // lexer output
	int		error;
    // optional/nice to have:
    // char *user;
    // char *cwd;
}   t_shell;


// t_string Functions
t_string *init_string(char *content);
t_string	*new_string(size_t cap);
char	advance(t_string *line);
char	peek(t_string *line);
char *realloc_string(t_string *word);
void	append(t_string *word, char c);
void    free_t_string(t_string *str);

// t_token Functions
t_token *create_token(char *lexeme, token_type type);
void	add_token(t_list **tokens, char *lexeme, token_type type);
void	free_token(void *ptr);
void	clear_tokens(t_list **tokens);

// Lexer & Scanners
int		tokenizer(t_shell *shell, t_string *line);
int 	scan_word(t_shell *shell, t_string *line);
int		scan_redirection(t_shell *shell, t_string *line);
int		scan_pipe(t_shell *shell, t_string *line);
void	expand(t_shell *shell, t_string *line, t_string *word);

// Expander


// Helpers
int	ft_isspace(char c);
char	**copy_env(char **envp);

// Tests
void	print_tokens(t_list *tokens);

// Error handling
void	error_report(t_shell *shell, char *error, int state);
void	error_exit(char *error);

// Shell functions
int	start_shell(t_shell *shell);
void	free_env(char **env);
void	reset_shell(t_shell *shell);