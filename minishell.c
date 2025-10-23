
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

int main(void)
{
	char		*input;
	t_env		*env_list;
	char **args;
	pid_t pid;
	char **envp;

	init_env(&env_list);
	while (1)
	{
		input = readline("minishell > ");
		if (!input || !input[0])
		{
			term_env(env_list);
			exit(0);
		}
		else
			add_history(input);
		args = ft_split(input, ' ');
		if (!ft_strncmp(args[0], "exit", 5))
		{
			exit_cmd(args, env_list);
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
		else if (!ft_strncmp(args[0], "clear", 6))
		{
			pid = fork();
			if (pid == 0)
			{
				envp = env_list_to_char(env_list);
				if (execve("/usr/bin/clear", args, envp))
				{
					free_arr(args);
					free_arr(envp);
					term_env(env_list);
					exit(1);
				}
			}
			else
			{
				waitpid(pid, NULL, 0);
				free_arr(args);
			}
		}
	}
	return 0;
}
