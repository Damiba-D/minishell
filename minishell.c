
#include "minishellD.h"

void exit_cmd(t_env *env_list, int exit_code)
{
	term_env(env_list);
	exit(exit_code);
}

int main(void)
{
	char		*input;
	t_env		*env_list;
	char *args[] = {"A", "B", "C"};

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
		if (!ft_strncmp(input, "exit", 5))
			exit_cmd(env_list, 0);
		if (!ft_strncmp(input, "env", 4))
			env_cmd(env_list);
		if (!ft_strncmp(input, "echo", 5))
		 	echo_cmd(args);
	}
	return 0;
}