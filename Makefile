make:
	cc -Wall -Wextra -Werror -lreadline minishell.c libft/libft.a -o minishell
clean:
	rm -f minishell