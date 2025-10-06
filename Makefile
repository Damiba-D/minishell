make:
	cc -Wall -Wextra -Werror -lreadline envfuncs.c minishell.c libft/libft.a -o minishell
clean:
	rm -f minishell