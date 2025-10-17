#include "minishellD.h"

int	cd_cmd(char **args, t_env **env_list)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	if (args[1] && args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (!args[1] || !ft_strncmp(args[1], "~", 2))
	{
		path = get_env_value("HOME", *env_list);
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	}
	else if (!ft_strncmp(args[1], "-", 2))
	{
		path = get_env_value("OLDPWD", *env_list);
		if (!path)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
		ft_putendl_fd(path, 1); // bash prints new dir after cd -
	}
	else
		path = args[1];
	old_pwd = get_env_value("PWD", *env_list);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	set_env_value("OLDPWD", old_pwd, env_list, false);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		set_env_value("PWD", new_pwd, env_list, false);
		free(new_pwd);
	}
	return (0);
}

