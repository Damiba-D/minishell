#include "../minishell.h"

static void exit_cmd_cleanup(unsigned char exit_code)
{
	ft_lstclear(&msh()->inputlst, free_input_node);
	term_env(msh()->env);
	restore_fds(msh()->og_fds);
	free(msh()->pids);
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

/// @brief 
/// @param context what exactly failed, IE, malloc or a command such as cd
/// @param detail extra info as to what failed, IE, a file that could not be opened
/// @param err flag used to print exact error message if function sets errno upon failure
void print_err(char *context, char *detail, bool err)
{
	ft_putstr_fd("minishell: ", 2);
	if (context)
	{
		ft_putstr_fd(context, 2);
		ft_putstr_fd(": ", 2);
	}
	if (detail && err)
		perror(detail);
	else if (detail)
		ft_putendl_fd(detail, 2);
	else if (err)
		ft_putendl_fd(strerror(errno), 2);
}

// For exiting
void error_exit(char *context, char *detail, int exit_code, bool err)
{
	print_err(context, detail, err);
	exit_cmd_cleanup(exit_code);
}
