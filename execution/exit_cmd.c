#include "../minishell.h"

static void exit_cmd_cleanup(unsigned char exit_code)
{
	ft_lstclear(&msh()->inputlst, free_input_node);
	term_env(msh()->env);
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

static bool	exit_parser(const char *str, long long *out)
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

int		exit_cmd(char **args)
{
	long long	exit_value;

	ft_putendl_fd("exit", 2);
	if (!args || !args[1])
		exit_cmd_cleanup((unsigned char)msh()->last_exit_status);
	exit_value = 0;
	if (!exit_parser(args[1], &exit_value))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit_cmd_cleanup(2);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	exit_cmd_cleanup((unsigned char)exit_value);
	return (0);
}

void malloc_err_exit(char *err_loc)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err_loc, 2);
	ft_putstr_fd(": Allocation Error\n", 2);
	exit_cmd_cleanup(1);
}

void	var_err_exit(char *err_msg, int err_code)
{
	if (err_msg)
		ft_putstr_fd(err_msg, 2);
	exit_cmd_cleanup(err_code);
}

void	file_err(char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	if (access(filename, F_OK))
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (access(filename, R_OK) || access(filename, W_OK))
		ft_putstr_fd(": Permission denied\n", 2);
}
