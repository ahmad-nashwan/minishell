# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
# include "../libft/libft.h"

typedef enum s_type
{
	WORD, PIPE,
	HEREDOC, OUT_RED, IN_RED, APPEND, 
	INVALID, END
} t_type;

typedef enum e_error
{
    ERR_NONE = 0,
    ERR_SYNTAX = 2,
    ERR_MALLOC = 1,
    ERR_CMD_NOT_FOUND = 127,
    ERR_PERMISSION = 126,
    ERR_NO_SUCH_FILE = 127,
    ERR_EXECVE = 1,
    ERR_BUILTIN = 1
} t_error;

typedef struct s_token 
{
	char *lexeme;
	t_type type;
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
	t_list 	*cmds;
	t_error	error_type;
	int		should_exit;
	char	*error_msg;
    // to add
    // char *user;
    // char *cwd;
}   t_shell;

typedef struct s_cmd
{
	t_list *argv_list; // the command and its arguments 
	t_list *redirections;
} t_cmd;

typedef struct s_redir
{
	t_type type;
	char *target;
} t_redir;


// t_string Functions
t_string 	*init_string(char *content);
t_string	*new_string(size_t cap);
char		advance(t_string *line);
char		peek(t_string *line);
char 		*realloc_string(t_string *word);
void		append(t_string *word, char c);
void    	free_t_string(t_string *str);

// t_token Functions
t_token 	*create_token(char *lexeme, t_type type);
void		add_token(t_list **tokens, char *lexeme, t_type type);
void		free_token(void *ptr);
void		clear_tokens(t_list **tokens);

// t_cmd & t_cmd list functions
t_cmd 		*cmd_create();
int 		cmd_add_arg(t_cmd *cmd, char *lexeme);
int 		cmd_add_redir(t_cmd *cmd, t_redir *redir);
void		cmd_free(void *p);
int 		cmd_list_add(t_list **cmd_list, t_cmd *cmd);
void 		cmd_list_clear(t_list **cmd_list);

// t_redir functions
t_redir 	*redir_create(t_type type, char *target);
void    redir_free(void *p);

// Tokenization & Scanners
int			tokenizer(t_shell *shell, t_string *line);
int 		scan_word(t_shell *shell, t_string *line);
int			scan_redirection(t_shell *shell, t_string *line);
int			scan_pipe(t_shell *shell, t_string *line);
void		expand(t_shell *shell, t_string *line, t_string *word, int quoted);

// Parsing
int	parse(t_shell *shell);


// Helpers
int			ft_isspace(char c);
char		**copy_env(char **envp);

// Tests
void		print_tokens(t_list *tokens);
void    	print_cmds(t_list *cmds);

// Error handling
void		report_error(t_shell *shell, t_error e, char *msg);
void		error_exit(char *error);

// Shell functions
int			start_shell(t_shell *shell);
void 		init_shell(t_shell *shell, char **envp);
void		free_env(char **env);
void		reset_shell(t_shell *shell);