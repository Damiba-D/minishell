#include "minishellD.h"

static void exit_cmd_cleanup(t_env *env_list, unsigned char exit_code)
{
	term_env(env_list);
	exit(exit_code);
}

int	exit_cmd(char **args, t_env *env_list)
{
	long	exit_code;
	int		i;

	ft_putendl_fd("exit", 1);
	if (!args[1])
		exit_cmd_cleanup(env_list, 0);
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	i = 0;
	while (args[1][i] && (ft_isdigit(args[1][i]) || 
			((args[1][i] == '+' || args[1][i] == '-') && i == 0)))
		i++;
	if (args[1][i] != '\0')
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_cmd_cleanup(env_list, 255);
	}
	exit_code = ft_atoi(args[1]);
	exit_cmd_cleanup(env_list, (unsigned char)exit_code);
	return (0);
}

void malloc_err_exit(t_env *env_list, char *err_loc)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err_loc, 2);
	ft_putstr_fd(": Allocation Error\n", 2);
	exit_cmd_cleanup(env_list, 1);
}
