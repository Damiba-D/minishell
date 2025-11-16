#include "../minishell.h"

int pwd_cmd(char **args, t_env *env_list)
{
	char *cwd;

	(void)args;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		cwd = get_env_value("PWD", env_list);
		if (cwd == NULL)
		{
			ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
			return (1);
		}
		else
		{
			printf("%s\n", cwd);
			return (0);
		}
	}
	else
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	return (0);
}
