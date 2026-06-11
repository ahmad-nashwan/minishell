/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:41:51 by anashwan          #+#    #+#             */
/*   Updated: 2026/06/10 14:35:40 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/* ************************************************************************** */
/*                                                                            */
/*                                   Colors                                   */
/*                                                                            */
/* ************************************************************************** */
/* Basic */
#define CLEAR       	"\033[2J\033[H"
#define RESET       	"\033[0m"
#define BOLD        	"\033[1m"
#define DIM         	"\033[2m"


#define CYAN        "\033[38;5;87m"
#define STEEL_BLUE      	"\033[38;5;111m"
#define VIOLET         	"\033[38;5;141m"


/* ************************************************************************** */
/*                                                                            */
/*                                     ENUMS                                  */
/*                                                                            */
/* ************************************************************************** */
typedef enum s_type
{
	WORD,
	PIPE,
	HEREDOC,
	APPEND,
	OUT_RED,
	IN_RED,
	AMBIG_REDIR,
	END
}								t_type;

typedef enum e_code
{
	OK,
	NONE,
	ERR,
	INTERRUPTED,
	SYNTAX_ERROR,
	INTERNAL_ERROR,
}								t_code;

/* ************************************************************************** */
/*                                                                            */
/*                               Data Structures                              */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_env_var
{
	char						*key;
	char						*value;
}								t_env_var;

typedef struct s_token
{
	char						*lexeme;
	t_type						type;
	int							quoted;
}								t_token;

typedef struct s_cmd
{
	t_list						*argv_list;
	t_list						*redirections;
}								t_cmd;

typedef struct s_redir
{
	t_type						type;
	char						*target;
	int							h_fd;
}								t_redir;

typedef struct s_string
{
	char						*str;
	size_t						index;
	size_t						cap;
	size_t						len;
}								t_string;

typedef struct s_shell
{
	t_list						*env_list;
	t_list						*tokens;
	t_list						*cmds;
	t_string					*curr_input;
	pid_t						*pids;
	t_code						error_type;
	int							exit_status;
	int							should_exit;
}								t_shell;

/* ************************************************************************** */
/*                                                                            */
/*                               Global Variables                             */
/*                                                                            */
/* ************************************************************************** */
extern volatile sig_atomic_t	g_signal;

/* ************************************************************************** */
/*                                                                            */
/*                                Shell Functions                             */
/*                                                                            */
/* ************************************************************************** */
int								start_shell(t_shell *shell);
void							init_shell(t_shell *shell, char **envp);
void							reset_shell(t_shell *shell);
void							free_shell_state(t_shell *shell);

/* ************************************************************************** */
/*                                                                            */
/*                             Structs functions                              */
/*                                                                            */
/* ************************************************************************** */
// t_string Functions
t_string						*init_string(char *content);
t_string						*create_empty_string(size_t cap);
char							advance(t_string *line);
char							peek(t_string *line);
t_code							realloc_string(t_string *word);
t_code							append(t_string *word, char c);
void							free_t_string(t_string *str);

// t_token Functions
t_token							*create_token(char *lexeme, t_type type,
									int quoted);
t_code							add_token(t_list **tokens, char *lexeme,
									t_type type, int quoted);
void							free_token(void *ptr);
void							clear_tokens(t_list **tokens);

// t_cmd & t_cmd list functions
t_cmd							*cmd_create(void);
t_code							cmd_add_arg(t_cmd *cmd, char *lexeme);
t_code							cmd_add_redir(t_cmd *cmd, t_redir *redir);
t_code							cmd_list_add(t_list **cmd_list, t_cmd *cmd);
void							cmd_free(void *p);
void							cmd_list_clear(t_list **cmd_list);

// t_redir functions
t_redir							*redir_create(t_type type, char *target);
void							redir_free(void *p);
int								is_hdoc_target(t_list *tokens);

// t_env
t_env_var						*create_env_var(char *env_str);
t_env_var						*new_env_var(const char *key,
									const char *value);
t_code							update_env_value(t_env_var *env,
									const char *value);
t_env_var						*find_env_var(t_list *env_list,
									const char *key);
void							free_env_var(void *content);
// env list
t_list							*init_env_list(char **envp);
t_code							add_env_var(t_list **env_list, t_env_var *var);
char							**env_to_array(t_list *env_list);
char							*get_env_value(t_list *env_vars,
									const char *key);

/* ************************************************************************** */
/*                                                                            */
/*                                    Parsing                                 */
/*                                                                            */
/* ************************************************************************** */
// Tokenization & Scanners
t_code							tokenizer(t_shell *shell, t_string *line);
t_code							scan_word(t_shell *shell, t_string *line);
t_code							scan_redirection(t_shell *shell,
									t_string *line);
t_code							scan_pipe(t_shell *shell, t_string *line);

// Expansion
t_code							expand_start(t_shell *shell, t_string *line,
									t_string *word, int quoted);
t_code							expand_tilde(t_shell *shell, t_string *line,
									t_string *word);
t_string						*get_var_name(t_string *line);
t_code							find_var_expand(t_shell *shell, t_string *line,
									t_string *word, int quoted);
t_code							expand_split(t_string *word, t_shell *shell,
									char *value);
t_code							expand_var(t_shell *shell, t_string *word,
									char *value, int quoted);
t_code							expand_exit_status(t_shell *shell,
									t_string *line, t_string *word, int quoted);
t_code							expand_hdoc(t_shell *shell, t_string *line,
									t_string *buff);
t_code							append_str(t_string *word, char *s);

// Parsing
t_code							parse(t_shell *shell);
t_code							build_cmd(t_shell *shell, t_cmd *cmd,
									t_list **node);
t_code							parse_redir(t_shell *shell, t_cmd *cmd,
									t_token *redir, t_token *target);
t_code							handle_redir_node(t_shell *shell, t_cmd *cmd,
									t_list **node, t_token *token);
t_code							parse_hdoc(t_shell *shell, char *delimeter,
									int *h_fd, int quoted);
char							*hdoc_read_line(void);
t_code							hdoc_append_char(t_shell *shell, t_string *line,
									t_string *buff, int quoted);
void							hdoc_eof_error(char *delimeter);

/* ************************************************************************** */
/*                                                                            */
/*                                   Execution                                */
/*                                                                            */
/* ************************************************************************** */
void							process_commands(t_shell *shell);
void							process_single_builtin(t_shell *shell,
									t_cmd *cmd);
void							process_pipeline(t_shell *shell);
t_code							run_builtin(t_shell *shell, t_cmd *cmd);
void							run_child(t_shell *shell, t_cmd *cmd,
									int input_fd, int *pipe_fd);
t_code							handle_redirections(t_cmd *cmd);
t_code							handle_hdoc(t_redir *redir);
void							close_hdoc_fds(t_list *cmds);

// Execution helpers
char							*get_valid_path(char **paths, char *cmd);
char							*find_cmd_path(t_shell *shell);
char							*build_full_path(char *dir, char *cmd);
int								is_builtin(char *name);
t_code							is_dir(char *path);
void							free_argv_envp_exit(t_shell *shell, char **argv,
									char **envp, int exit_code);
void							exit_child(t_shell *shell, int exit_state);

/* ************************************************************************** */
/*                                                                            */
/*                                   Builtins                                 */
/*                                                                            */
/* ************************************************************************** */
void							env(t_shell *shell, t_list *args);
void							pwd(t_shell *shell);
void							echo(t_shell *shell, t_list *args);
void							shell_exit(t_shell *shell, t_list *args);
void							cd(t_shell *shell, t_list *args);
void							unset(t_shell *shell, t_list *args);
void							export(t_shell *shell, t_list *args);

// export helpers
t_code							export_variables(t_list **env_list,
									t_list *args);
t_code							export_print(t_list *env_list);

/* ************************************************************************** */
/*                                                                            */
/*                                   Signals                                  */
/*                                                                            */
/* ************************************************************************** */
void							sig_set_interactive(void);
void							sig_set_execution(void);
void							sig_set_child(void);
void							sig_set_heredoc(void);
void							sigint_interactive_handler(int sig);
void							sigint_hdoc_handler(int sig);

/* ************************************************************************** */
/*                                                                            */
/*                             Error handling                                 */
/*                                                                            */
/* ************************************************************************** */
void							report_error(t_shell *shell, t_code e,
									char *msg);
void							error_exit(char *error);
t_code							report_syntax_error(char *bad_token);
t_code							parse_error(t_shell *shell, t_cmd *cmd,
									t_list **cmd_list, t_code error);
void							print_cmd_error(char *cmd, char *msg);
t_code							split_error(char **words, t_code rc);

/* ************************************************************************** */
/*                                                                            */
/*                                General Helpers                             */
/*                                                                            */
/* ************************************************************************** */
int								ft_isspace(char c);
char							**copy_env(char **envp);
void							free_split(char **words);
int								safe_atol(const char *str, long *out);
int								is_number(char *arg);
int								ft_strcmp(const char *s1, const char *s2);
char							**list_to_string_array(t_list *list);
void							free_strings_array(char **arr);
void							free_array(char **arr, int elements);
<<<<<<< HEAD

/* ************************************************************************** */
/*                                                                            */
/*                                     Theme                                  */
/*                                                                            */
/* ************************************************************************** */
void    print_banner(t_shell *shell);
void	print_prompt_line(t_shell *shell);
=======
void 							check_shell_level(t_list *env_list);
// we may remove this
>>>>>>> ef418e3 (fix : readded the check_shlvl function and fixed the SHLVL env)

#endif