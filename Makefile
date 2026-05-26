NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

INC_DIR = inc
LIBFT_DIR = libft

INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)

LIBFT = $(LIBFT_DIR)/libft.a

READLINE = -lreadline -lhistory -lncurses

SRC = \
	src/main.c \
	src/shell.c \
	src/error_handling/error_handling.c \
	src/structs/t_token.c \
	src/structs/t_string.c \
	src/structs/t_cmd.c \
	src/structs/t_cmd_list.c \
	src/structs/t_redir.c \
	src/structs/t_env_var.c \
	src/env/env_list_utils.c \
	src/env/env_to_array.c \
	src/tokenizer/tokenizer.c \
	src/tokenizer/expander/expand_start.c \
	src/tokenizer/expander/expand_vars.c \
	src/tokenizer/expander/expand_split.c \
	src/tokenizer/expander/expand_exit_status.c \
	src/tokenizer/expander/expand_hdoc.c \
	src/tokenizer/scan_pipe.c \
	src/tokenizer/scan_redirection.c \
	src/tokenizer/scan_word.c \
	src/parsing/parse_start.c \
	src/parsing/parse_build_cmd.c \
	src/parsing/parse_hdoc.c \
	src/parsing/parse_hdoc_utils.c \
	src/parsing/parse_errors.c \
	src/builtins/echo.c \
	src/builtins/pwd.c \
	src/builtins/env.c \
	src/builtins/exit.c \
	src/builtins/cd.c \
	src/builtins/export/export.c \
	src/builtins/export/export_print.c \
	src/builtins/export/export_variables.c \
	src/builtins/unset.c \
	src/execution/execution_utils.c \
	src/execution/handle_redirections.c \
	src/execution/handle_heredoc.c \
	src/execution/process_commands.c \
	src/execution/process_single_builtin.c \
	src/execution/process_pipeline.c \
	src/execution/run_command.c \
	src/execution/run_builtin.c \
	src/signals/sig_settings.c \
	src/signals/sig_handlers.c \
	src/utils/helpers.c \
	src/utils/safe_atol.c \
	src/utils/shell_utils.c \
	src/utils/string_utils.c \
	src/utils/array_utils.c \
	src/tests/print_tokens.c \
	src/tests/print_cmds.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT): $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READLINE) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re