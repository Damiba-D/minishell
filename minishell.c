
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
	char *args[] = {"unset", "1VAR", "NEWVAR", "BIGVAR", NULL};

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
		if (!ft_strncmp(input, "unset", 6))
		 	unset_cmd(args, &env_list);
		if (!ft_strncmp(input, "export", 7))
		{
			set_env_value("NEWVAR", "your mom a hoe", &env_list);
			set_env_value("BIGVAR", "yo moma so fat", &env_list);
			set_env_value("UGLYVAR", "yo moma so ugly", &env_list);
		} //COLORTERM=truecolor
	}
	return 0;
}