SRCS = minishell.c data.c parsing/arg_split.c parsing/copying.c \
		parsing/counting.c parsing/extract_reds.c parsing/parse_line.c \
		parsing/check_reds.c parsing/free_hub.c parsing/utils.c
OBJS = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	cc -Wall -Wextra -Werror $(OBJS) libft/libft.a -lreadline -o $(NAME)

%.o: %.c
	cc -Wall -Wextra -Werror -c $< -o $@

libft/libft.a:
	make -C libft

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re