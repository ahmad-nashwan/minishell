# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
# include "../libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>

typedef enum s_type
{
	WORD, PIPE,
	HEREDOC, OUT_RED, IN_RED, APPEND, 
	INVALID, END
} t_type;

typedef enum e_code
{
    OK = 0,
    NONE = 1,
    SYNTAX_ERROR = 3,
    UNCLOSED_QUOTES = 4,
    PIPE_ERROR = 5,
    REDIR_ERROR = 6,
    INTERNAL_ERROR = 7,
    CMD_NOT_FOUND = 8,
    PERMISSION_DENIED = 9,
    EXEC_ERROR = 10,
    BUILTIN_ERROR = 11,
    ERR
} t_code;

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
	t_code	error_type;
	int		should_exit;
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


// Shell functions & utils
int			start_shell(t_shell *shell);
void 		init_shell(t_shell *shell, char **envp);
void		free_env(char **env);
void		reset_shell(t_shell *shell);

// t_string Functions
t_string 	*init_string(char *content);
t_string	*new_string(size_t cap);
char		advance(t_string *line);
char		peek(t_string *line);
char 		*realloc_string(t_string *word);
t_code		append(t_string *word, char c);
void    	free_t_string(t_string *str);

// t_token Functions
t_token 	*create_token(char *lexeme, t_type type);
t_code		add_token(t_list **tokens, char *lexeme, t_type type);
void		free_token(void *ptr);
void		clear_tokens(t_list **tokens);

// t_cmd & t_cmd list functions
t_cmd 		*cmd_create();
t_code 		cmd_add_arg(t_cmd *cmd, char *lexeme);
t_code 		cmd_add_redir(t_cmd *cmd, t_redir *redir);
t_code      cmd_list_add(t_list **cmd_list, t_cmd *cmd);
void		cmd_free(void *p);
void 		cmd_list_clear(t_list **cmd_list);

// t_redir functions
t_redir 	*redir_create(t_type type, char *target);
void        redir_free(void *p);

// Tokenization & Scanners
t_code		tokenizer(t_shell *shell, t_string *line);
t_code 		scan_word(t_shell *shell, t_string *line);
t_code		scan_redirection(t_shell *shell, t_string *line);
t_code		scan_pipe(t_shell *shell, t_string *line);

// expansion
t_code	    init_expand(t_shell *shell, t_string *line, t_string *word, int quoted);
t_code      get_var_value(t_shell *shell, t_string *name, t_string **value);
t_string    *get_var_name(t_string *line);
t_code      find_variable_expand(t_shell *shell, t_string *line, t_string *word, int quoted);
t_code      expand_split(t_string *word, t_shell *shell, char *value);
t_code	    expand_var(t_shell *shell, t_string *word, char *value, int quoted);
t_code      expand_exit_status(t_shell *shell, t_string *line, t_string *word, int quoted);

// Parsing
t_code      parse(t_shell *shell);


// Helpers
int			ft_isspace(char c);
char		**copy_env(char **envp);
void	    free_split(char **words);

// Tests
void		print_tokens(t_list *tokens);
void    	print_cmds(t_list *cmds);

// Error handling
void	    report_error(t_shell *shell, t_code e, char *msg);
void		error_exit(char *error);
t_code      handle_error(t_shell *shell);

// Shell functions
int			start_shell(t_shell *shell);
void		free_env(char **env);
void		reset_shell(t_shell *shell);

// Excution
void execute (t_list *cmds);
void executer(t_shell *shell);
