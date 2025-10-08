
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
		if (!strncmp(input, "exit", 5))
			exit_cmd(env_list, 0);
		if (!strncmp(input, "env", 4))
			env_cmd(env_list);
	}
	return 0;
}