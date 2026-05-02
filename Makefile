NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

INC_DIR = inc
LIBFT_DIR = libft
LIBFT_REPO = https://github.com/nopresentation/libft.git

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
	src/tokenizer/expander.c \
	src/tokenizer/scan_pipe.c \
	src/tokenizer/scan_redirection.c \
	src/tokenizer/scan_word.c \
	src/parsing/parsing.c \
	src/utils/helpers.c \
	src/tests/print_tokens.c \
	src/tests/print_cmds.c \
	

OBJ = $(SRC:.c=.o)

all: $(NAME)

# clone libft if it doesn't exist
$(LIBFT_DIR):
	git clone $(LIBFT_REPO) $(LIBFT_DIR)

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