# -------------------
# PROJECT
# -------------------
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# -------------------
# DIRECTORIES
# -------------------
SRC_DIR = src
LIBFT_DIR = libft
INC_DIR = inc

# -------------------
# SOURCES
# -------------------
SRCS = $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(SRC_DIR)/lexer/*.c) \
       $(wildcard $(SRC_DIR)/structs/*.c) \
       $(wildcard $(SRC_DIR)/tests/*.c) \
       $(wildcard $(SRC_DIR)/utils/*.c)

OBJS = $(SRCS:.c=.o)

# -------------------
# LIBRARIES
# -------------------
LIBFT = $(LIBFT_DIR)/libft.a
READLINE = -lreadline

# -------------------
# DEFAULT
# -------------------
all: $(LIBFT) $(NAME)

# -------------------
# BUILD LIBFT
# -------------------
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# -------------------
# BUILD MINISHELL
# -------------------
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

# -------------------
# COMPILE .c -> .o
# -------------------
%.o: %.c
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) -c $< -o $@

# -------------------
# CLEAN
# -------------------
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

# -------------------
# PHONY
# -------------------
.PHONY: all clean fclean re