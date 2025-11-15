# **************************************************************************** #
#                               MASTER MAKEFILE                                #
# **************************************************************************** #

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
RLFLAG      = -lreadline

# Independent sources
SRCS        = minishell.c data.c
OBJS        = $(SRCS:.c=.o)

# Directories
LIBFT_DIR   = libft
EXEC_DIR    = execution
PARS_DIR    = parsing

# Libraries
LIBFT_A     = $(LIBFT_DIR)/libft.a
EXEC_A      = $(EXEC_DIR)/execution.a
PARS_A      = $(PARS_DIR)/parsing.a

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(LIBFT_A) $(EXEC_A) $(PARS_A) $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(EXEC_A) $(PARS_A)
	@echo "🔗 Linking minishell..."
	@$(CC) $(CFLAGS) $(OBJS) $(EXEC_A) $(PARS_A) $(LIBFT_A) $(RLFLAG) -o $(NAME)
	@echo "✅ minishell compiled successfully!"

# ---------------------------------------------------------------------------- #
#                  Object Compilation (requires libft to exist)                #
# ---------------------------------------------------------------------------- #

%.o: %.c $(LIBFT_A)
	@echo "🧩 Compiling $<"
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

# ---------------------------------------------------------------------------- #
#                              Library Compilation                             #
# ---------------------------------------------------------------------------- #

$(LIBFT_A):
	@echo "📚 Building libft..."
	@$(MAKE) -s -C $(LIBFT_DIR)

$(EXEC_A): $(LIBFT_A)
	@echo "📦 Building execution.a..."
	@$(MAKE) -s -C $(EXEC_DIR)

$(PARS_A): $(LIBFT_A)
	@echo "📦 Building parsing.a..."
	@$(MAKE) -s -C $(PARS_DIR)

# ---------------------------------------------------------------------------- #
#                                   Cleaning                                   #
# ---------------------------------------------------------------------------- #

clean:
	@echo "🧹 Cleaning master objects..."
	@rm -f $(OBJS)

	@echo "🧹 Cleaning libft objects..."
	@$(MAKE) -s -C $(LIBFT_DIR) clean

	@echo "🧹 Cleaning execution objects..."
	@$(MAKE) -s -C $(EXEC_DIR) clean

	@echo "🧹 Cleaning parsing objects..."
	@$(MAKE) -s -C $(PARS_DIR) clean

fclean: clean
	@echo "💣 Removing minishell executable..."
	@rm -f $(NAME)

	@echo "💣 Removing libft.a..."
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

	@echo "💣 Removing execution.a..."
	@$(MAKE) -s -C $(EXEC_DIR) fclean

	@echo "💣 Removing parsing.a..."
	@$(MAKE) -s -C $(PARS_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
