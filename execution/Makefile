# **************************************************************************** #
#                                   Makefile                                   #
# **************************************************************************** #

# Library name
NAME        = execution.a

# Compiler and flags
CC          = cc
CFLAGS      = -g -Wall -Wextra -Werror

# Directories
SRC_DIR     = .
OBJ_DIR     = obj
LIBFT_DIR   = ../libft


LIBFT_A     = $(LIBFT_DIR)/libft.a

# Sources
SRCs        = envfuncs.c envfuncs2.c env_cmd.c unset_cmd.c echo_cmd.c cd_cmd.c \
			  export_cmd/export_utils.c export_cmd/export_cmd.c \
			  exit_cmd.c pwd_cmd.c executor/executor_utils.c executor/builtin_utils.c executor/extcmd_utils.c \
			  executor/here_doc.c executor/execute_pipeline.c executor/executor.c

OBJ         = $(addprefix $(OBJ_DIR)/, $(SRCs:.c=.o))

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
