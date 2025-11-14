#include "minishellD.h"

static void exit_cmd_cleanup(char **args, t_env *env_list, unsigned char exit_code)
{
	free_arr(args);
	term_env(env_list);
	exit(exit_code);
}

static bool	is_numeric(const char *s)
{
	int i;

	i = 0;
	if (!s || !*s)
		return (false);
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!ft_isdigit(s[i]))
		return (false);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	exit_parser(const char *str, long long *out)
{
	int			sign;
	int			i;
	int			digit;

	if (!is_numeric(str))
		return (false);
	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i])
	{
		digit = str[i++] - '0';
		if (sign == 1 && (*out > (LLONG_MAX - digit) / 10))
			return (false);
		if (sign == -1 && (-(*out) < (LLONG_MIN + digit) / 10))
			return (false);
		*out = *out * 10 + digit;
	}
	*out *= sign;
	return (true);
}

int		exit_cmd(char **args, t_env *env_list)
{
	long long	exit_value;

	ft_putendl_fd("exit", 2);
	if (!args[1])
		exit_cmd_cleanup(args, env_list, 0);
	exit_value = 0;
	if (!exit_parser(args[1], &exit_value))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit_cmd_cleanup(args, env_list, 2);
	}
	if (args[2])
	{
		free_arr(args);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	exit_cmd_cleanup(args, env_list, (unsigned char)exit_value);
	return (0);
}

void malloc_err_exit(t_env *env_list, char *err_loc)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err_loc, 2);
	ft_putstr_fd(": Allocation Error\n", 2);
	exit_cmd_cleanup(NULL, env_list, 1);
}
