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
	src/tokenizer/tokenizer.c \
	src/tokenizer/expander/init_expand.c \
	src/tokenizer/expander/find_expand.c \
	src/tokenizer/expander/expand_split.c \
	src/tokenizer/expander/expand_exit.c \
	src/tokenizer/scan_pipe.c \
	src/tokenizer/scan_redirection.c \
	src/tokenizer/scan_word.c \
	src/parsing/parsing.c \
	src/parsing/syntax_errors.c \
	src/builtins/builtins.c \
	src/builtins/echo.c \
	src/builtins/pwd.c \
	src/utils/excution_utils.c \
	src/utils/helpers.c \
	src/utils/shell_utils.c \
	src/tests/print_tokens.c \
	src/tests/print_cmds.c \
	src/execution/excute.c \
	src/execution/excuter.c \
	src/execution/handle_redirections.c
	
OBJ = $(SRC:.c=.o)

all: $(NAME)

# build libft
$(LIBFT): $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) bonus

# build program
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
