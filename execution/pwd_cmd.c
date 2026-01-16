/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:47:35 by ddamiba           #+#    #+#             */
/*   Updated: 2026/01/16 17:47:36 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_cmd(char **args)
{
	char	*cwd;

	(void)args;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		cwd = get_env_value("PWD", msh()->env);
		if (cwd == NULL)
		{
			ft_putstr_fd("pwd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory\n", 2);
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
