#include "minishellD.h"

static void print_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

static int set_path(char **args, t_env *env_list, char **path)
{
	if (!args[1] || !ft_strncmp(args[1], "~", 2))
	{
		*path = get_env_value("HOME", env_list);
		if (!(*path))
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	}
	else if (!ft_strncmp(args[1], "-", 2))
	{
		*path = get_env_value("OLDPWD", env_list);
		if (!(*path))
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
		ft_putendl_fd(*path, 1);
	}
	else
		*path = args[1];
	return (0);
}

int	cd_cmd(char **args, t_env **env_list)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	if (args[1] && args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (set_path(args, *env_list, &path))
		return (1);
	old_pwd = get_env_value("PWD", *env_list);
	if (chdir(path) != 0)
		return (print_error(path), 1);
	set_env_value("OLDPWD", old_pwd, env_list, false);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
		return(set_env_value("PWD", new_pwd, env_list, false), free(new_pwd), 0);
	else
	{
		free_arr(args);
		malloc_err_exit(*env_list, "cd");
	}
	return (0);
}

