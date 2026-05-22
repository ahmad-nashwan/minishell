#include "../libft/libft.h"
#include <stdio.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

typedef enum s_type
{
	WORD,
	PIPE,
	HEREDOC,
	OUT_RED,
	IN_RED,
	APPEND,
	INVALID,
	END
}			t_type;

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
}			t_code;

typedef struct s_token
{
	char	*lexeme;
	t_type	type;
}			t_token;

typedef struct s_string
{
	char	*str;
	size_t	index;
	size_t	cap;
	size_t	len;
}			t_string;

typedef struct s_env_var
{
    char    *key;
    char    *value;
} t_env_var;

typedef struct s_shell
{
	t_list 	*env_list;
	char	*cwd;
	int		exit_status;
	t_list	*tokens;
	t_list	*cmds;
	t_code	error_type;
	int		should_exit;
}			t_shell;

typedef struct s_cmd
{
	t_list	*argv_list;
	t_list	*redirections;
}			t_cmd;

typedef struct s_redir
{
	t_type	type;
	char	*target;
}			t_redir;


// Shell functions & utils
int			start_shell(t_shell *shell);
void		init_shell(t_shell *shell, char **envp);
void		reset_shell(t_shell *shell);

// t_string Functions
t_string	*init_string(char *content);
t_string	*new_string(size_t cap);
char		advance(t_string *line);
char		peek(t_string *line);
char		*realloc_string(t_string *word);
t_code		append(t_string *word, char c);
void		free_t_string(t_string *str);

// t_token Functions
t_token		*create_token(char *lexeme, t_type type);
t_code		add_token(t_list **tokens, char *lexeme, t_type type);
void		free_token(void *ptr);
void		clear_tokens(t_list **tokens);

// t_cmd & t_cmd list functions
t_cmd		*cmd_create(void);
t_code		cmd_add_arg(t_cmd *cmd, char *lexeme);
t_code		cmd_add_redir(t_cmd *cmd, t_redir *redir);
t_code		cmd_list_add(t_list **cmd_list, t_cmd *cmd);
void		cmd_free(void *p);
void		cmd_list_clear(t_list **cmd_list);

// t_redir functions
t_redir		*redir_create(t_type type, char *target);
void		redir_free(void *p);

// t_env
t_env_var   *new_env_var(const char *key, const char *value);
t_env_var 	*find_env_var(t_list *env_list, const char *key);
t_code  	update_env_value(t_env_var *env, const char *value);
t_code 		add_env_var(t_list **env_list, t_env_var *var);
void    	free_env_var(void *content);
char    	**get_env_array(t_list *env_list);
void 		free_array(char **arr, int elements);

// Tokenization & Scanners
t_code		tokenizer(t_shell *shell, t_string *line);
t_code		scan_word(t_shell *shell, t_string *line);
t_code		scan_redirection(t_shell *shell, t_string *line);
t_code		scan_pipe(t_shell *shell, t_string *line);

// Expansion
t_code		init_expand(t_shell *shell, t_string *line, t_string *word,
				int quoted);
t_string	*get_var_name(t_string *line);
t_code		find_variable_expand(t_shell *shell, t_string *line, t_string *word,
				int quoted);
t_code		expand_split(t_string *word, t_shell *shell, char *value);
t_code		expand_var(t_shell *shell, t_string *word, char *value, int quoted);
t_code		expand_exit_status(t_shell *shell, t_string *line, t_string *word,
				int quoted);
t_code 		append_str(t_string *word, char *s);

// Parsing
t_code		parse(t_shell *shell);

// Helpers
int			ft_isspace(char c);
char		**copy_env(char **envp);
char		*get_env_value(t_list *env_vars, const char *key);
void		free_split(char **words);
int			safe_atol(const char *str, long *out);
int			is_number(char *arg);
int 		ft_strcmp(const char *s1, const char *s2);
void		free_strings_array(char **arr, int size);
char		**list_to_array(t_list *list);;

// Tests
void		print_tokens(t_list *tokens);
void		print_cmds(t_list *cmds);

// Error handling
void		report_error(t_shell *shell, t_code e, char *msg);
void		error_exit(char *error);
t_code		handle_error(t_shell *shell);
t_code		report_syntax_error(char *bad_token);
t_code		parse_error(t_shell *shell, t_cmd *cmd, t_list **cmd_list,
				t_code error);
// Execution
t_code		process_commands(t_shell *shell);
t_code		process_pipeline(t_shell *shell);
t_code		run_builtin(t_shell *shell, t_cmd *cmd);
t_code 		run_child(t_shell *shell, t_cmd *cmd, int input_fd, int *pipe_fd);
t_code  	handle_redirections(t_shell *shell, t_cmd *cmd);

char    	*get_valid_path(char **paths, char *cmd);

char		*find_cmd_path(t_shell *shell);
t_code		exec_absolute_path(char **argv, char **envp);
char		*build_full_path(char *dir, char *cmd);
t_code		search_and_exec(t_shell *shell, char **argv, char **envp);
t_code		exec_from_path( char **argv, char **path_list, char **envp);
int			is_builtin(char *name);
t_env_var 	*find_env_var(t_list *env_list, const char *key);

t_code 		add_env_var(t_list **env_list, t_env_var *var);
t_code		print_export(t_shell *shell);

// Built-in functions
void		env(t_shell *shell, t_list *args);
void  		pwd(t_shell *shell);
void  		echo(t_shell *shell, t_list *args);
void		shell_exit(t_shell *shell, t_list *args);
void		cd(t_shell *shell, t_list *args);
void		unset(t_shell *shell, t_list *args);

// export
void		export(t_shell *shell, t_list *args);
t_code	 	export_variables(t_list **env_list, t_list *args);
t_code 		export_print(t_list *env_list);


t_env_var   *create_env_var(char *env_str);
t_list      *init_env_list(char **envp);
char        *get_env_val(t_list *env_list, const char *key);
t_code      set_env_var(t_list **env_list, const char *key, const char *value);
void        free_env_var(void *content);