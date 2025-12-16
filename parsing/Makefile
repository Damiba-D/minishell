# **************************************************************************** #
#                                   Makefile                                   #
# **************************************************************************** #

# Library name
NAME        = parsing.a

# Compiler and flags
CC          = cc
CFLAGS      = -g -Wall -Wextra -Werror

# Directories
SRC_DIR     = .
OBJ_DIR     = obj
LIBFT_DIR   = ../libft

# External library (used, but never built/cleaned here)
LIBFT_A     = $(LIBFT_DIR)/libft.a

# Sources (WITHOUT minishell.c)
SRCS        = arg_split.c copying.c \
			  counting.c extract_reds.c \
			  parse_line.c free_hub.c utils.c \
			  signals.c expansion.c expansion_utils.c \
			  expansion_utils2.c quotes_removal.c refactoring.c

OBJ         = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Includes
INCLUDES    = -I. -I$(LIBFT_DIR)

# Colors
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
RED         = \033[1;31m
RESET       = \033[0m

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(BLUE)📚 Creating static library $(NAME)...$(RESET)"
	@ar rcs $(NAME) $(OBJ) $(LIBFT_A)
	@echo "$(GREEN)✅ Library $(NAME) built successfully!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)🧩 Compiling:$(RESET) $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)🧹 Object files cleaned.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)💣 Library removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
