# **************************************************************************** #
#                                   Makefile                                   #
# **************************************************************************** #

# Program name
NAME        = minishell

# Compiler and flags
CC          = cc
CFLAGS      = -g -Wall -Wextra -Werror
RLFLAG		= -lreadline

# Directories
SRC_DIR     = .
OBJ_DIR     = obj
LIBFT_DIR   = libft
PRINTF_DIR  = $(LIBFT_DIR)/ft_printf
GNL_DIR     = $(LIBFT_DIR)/get_next_line

# Libraries
LIBFT_A     = $(LIBFT_DIR)/libft.a
PRINTF_A    = $(PRINTF_DIR)/libftprintf.a
GNL_A       = $(GNL_DIR)/get_next_line.a

# Sources and objects
SRC         = envfuncs.c envfuncs2.c env_cmd.c unset_cmd.c echo_cmd.c cd_cmd.c export_cmd.c minishell.c
OBJ         = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Includes
INCLUDES    = -I. -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(GNL_DIR)

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
	@echo "$(YELLOW)🔧 Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(BLUE)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(PRINTF_A) $(GNL_A) $(RLFLAG) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(BLUE)🧩 Compiling:$(RESET) $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)🧹 Object files cleaned.$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@rm -f $(NAME)
	@echo "$(BLUE)💣 All binaries removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
