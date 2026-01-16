/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extcmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:46:11 by ddamiba           #+#    #+#             */
/*   Updated: 2026/01/16 17:46:12 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "executor.h"

char	*find_command(t_input *input, char *path)
{
	char	*temp;
	char	**dirs;
	int		i;
	char	*full_path;

	dirs = ft_split(path, ':');
	if (!dirs)
		error_exit("malloc", "Allocation Error", 1, false);
	i = 0;
	while (dirs[i])
	{
		temp = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(temp, input->argv[0]);
		free(temp);
		if (!full_path)
		{
			free_arr(dirs);
			error_exit("malloc", "Allocation Error", 1, false);
		}
		if (access(full_path, X_OK) == 0)
			return (free_arr(dirs), full_path);
		free(full_path);
		i++;
	}
	return (free_arr(dirs), NULL);
}

char	*cmd_create(t_input *input)
{
	char		*path;
	char		*cmd;
	struct stat	statbuf;

	cmd = NULL;
	if (ft_strchr(input->argv[0], '/'))
	{
		if (stat(input->argv[0], &statbuf) != 0)
			error_exit(input->argv[0], "No such file or directory", 127, false);
		if (S_ISDIR(statbuf.st_mode))
			error_exit(input->argv[0], "Is a directory", 126, false);
		if (access(input->argv[0], X_OK) != 0)
			error_exit(input->argv[0], "Permission denied", 126, false);
		cmd = ft_strdup(input->argv[0]);
		if (!cmd)
			error_exit("malloc", "Allocation Error", 1, false);
		return (cmd);
	}
	path = get_env_value("PATH", msh()->env);
	if (path)
		cmd = find_command(input, path);
	if (!cmd)
		error_exit(input->argv[0], "command not found", 127, false);
	return (cmd);
}

static void	wait_child(void)
{
	int	w_status;
	int	sig;

	wait(&w_status);
	if (WIFEXITED(w_status))
		msh()->last_exit_status = WEXITSTATUS(w_status);
	else if (WIFSIGNALED(w_status))
	{
		sig = WTERMSIG(w_status);
		if (sig == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
		msh()->last_exit_status = 128 + sig;
	}
}

static void	cleanup_execve(char *cmd, char **env, char *cmd_name)
{
	free(cmd);
	free_arr(env);
	error_exit(NULL, cmd_name, 1, true);
}

void	execute_ext_cmd(t_input *input)
{
	pid_t	pid;
	char	**env;
	char	*cmd;

	pid = fork();
	if (pid == -1)
		return (msh()->last_exit_status = 1, print_err("fork", NULL, true));
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (setup_fds(input, msh()->og_fds, true))
			error_exit(NULL, NULL, 1, false);
		cmd = cmd_create(input);
		env = env_list_to_char(msh()->env);
		if (env == NULL)
			return (free(cmd), error_exit("malloc", \
"Allocation Error", 1, false));
		if (execve(cmd, input->argv, env))
			cleanup_execve(cmd, env, input->argv[0]);
	}
	wait_child();
}
