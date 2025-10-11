
#include "minishellD.h"

void	free_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void malloc_err_exit(t_env *env_list, char *err_loc)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err_loc, 2);
	ft_putstr_fd(": Allocation Error\n", 2);
	exit_cmd(env_list, 1);
}

void exit_cmd(t_env *env_list, unsigned char exit_code)
{
	term_env(env_list);
	exit(exit_code);
}

int main(void)
{
	char		*input;
	t_env		*env_list;
	char *args[] = {"export", NULL};

	init_env(&env_list);
	unset_cmd(args, &env_list);
	set_env_value("PATHNAME", "your mom a hoe", &env_list);
	while (1)
	{
		input = readline("minishell > ");
		if (!input || !input[0])
		{
			exit_cmd(env_list, 1);
		}
		else
			add_history(input);
		if (!ft_strncmp(input, "exit", 5))
			exit_cmd(env_list, 0);
		if (!ft_strncmp(input, "env", 4))
			env_cmd(env_list);
		if (!ft_strncmp(input, "echo", 5))
		 	echo_cmd(args);
		if (!ft_strncmp(input, "unset", 6))
		 	unset_cmd(args, &env_list);
		if (!ft_strncmp(input, "export", 7))
		 	export_cmd(args, &env_list);
		if (!ft_strncmp(input, "array", 6))
		{
			char **arr = env_list_to_char(env_list);
			for (int i = 0; arr[i]; i++)
			{
				printf("%s\n", arr[i]);
			}
			free_arr(arr);
		} //COLORTERM=truecolor
	}
	return 0;
}