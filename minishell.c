
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
	free(arr[i]);
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
	char **args;

	init_env(&env_list);
	while (1)
	{
		input = readline("minishell > ");
		if (!input || !input[0])
		{
			exit_cmd(env_list, 1);
		}
		else
			add_history(input);
		args = ft_split(input, ' ');
		if (!ft_strncmp(args[0], "exit", 5))
		{
			free_arr(args);
			exit_cmd(env_list, 0);
		}
		else if (!ft_strncmp(args[0], "env", 4))
		{
			env_cmd(env_list);
			free_arr(args);
		}
		else if (!ft_strncmp(args[0], "echo", 5))
		{
		 	echo_cmd(args);
			free_arr(args);
		}
		else if (!ft_strncmp(args[0], "unset", 6))
		{
		 	unset_cmd(args, &env_list);
			free_arr(args);
		}
		else if (!ft_strncmp(args[0], "export", 7))
		{
		 	export_cmd(args, &env_list);
			free_arr(args);
		}
		else if (!ft_strncmp(args[0], "pwd", 4))
		{
			pwd_cmd(args, env_list);
			free_arr(args);
		}
		else if (!ft_strncmp(args[0], "cd", 3))
		{
			cd_cmd(args, &env_list);
			free_arr(args);
			printf("PWD: %s, OLDPWD: %s\n" , get_env_value("PWD", env_list), get_env_value("OLDPWD", env_list));
		}
	}
	return 0;
}
