/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:46:47 by ddamiba           #+#    #+#             */
/*   Updated: 2026/01/16 17:46:48 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	set_path(char **args, t_env *env_list, char **path)
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

int	cd_cmd(char **args)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	if (args[1] && args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 2);
	if (set_path(args, msh()->env, &path))
		return (1);
	old_pwd = get_env_value("PWD", msh()->env);
	if (chdir(path) != 0)
		return (print_err("cd", path, true), 1);
	set_env_value("OLDPWD", old_pwd, &msh()->env, false);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		set_env_value("PWD", new_pwd, &msh()->env, false);
		return (free(new_pwd), 0);
	}
	else
	{
		set_env_value("PWD", args[1], &msh()->env, true);
		ft_putendl_fd("cd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory", 2);
	}
	return (0);
}
