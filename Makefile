NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

INC_DIR = inc
LIBFT_DIR = libft

INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)

LIBFT = $(LIBFT_DIR)/libft.a

# Linux readline (important)
READLINE = -lreadline -lhistory -lncurses

SRC = \
	src/main.c \
	src/shell.c \
	src/error_handling/error_handling.c \
	src/structs/tokens.c \
	src/structs/t_string.c \
	src/tests/print_tokens.c \
	src/tokenizer/tokenizer.c \
	src/tokenizer/expander.c \
	src/tokenizer/scan_pipe.c \
	src/tokenizer/scan_redirection.c \
	src/tokenizer/scan_word.c \
	src/utils/helpers.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

# Build libft first
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

# Link everything
$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READLINE) -o $(NAME)

# Compile objects
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