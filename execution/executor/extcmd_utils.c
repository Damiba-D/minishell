#include "../../minishell.h"
#include "executor.h"

char	*find_command(t_input *input, char *path)
{
	char *temp;
	char **dirs;
	int i;
	char *full_path;

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
	char *path;
	char *cmd;

	if (ft_strchr(input->argv[0], '/'))
	{
		if (access(input->argv[0], F_OK) != 0)
			error_exit(input->argv[0], "command not found", 127, false);
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
	else
		cmd = NULL;
	if (!cmd)
		error_exit(input->argv[0], "command not found", 127, false);
	return (cmd);
}

static void wait_child(void)
{
	int w_status;

	wait(&w_status);
	if (WIFEXITED(w_status))
		msh()->last_exit_status = WEXITSTATUS(w_status);
	else if (WIFSIGNALED(w_status))
		msh()->last_exit_status = 128 + WTERMSIG(w_status);
}

void execute_ext_cmd(t_input *input)
{
	pid_t pid;
	char **env;
	char *cmd;

	pid = fork();
	if (pid == -1)
		return (msh()->last_exit_status = 1, print_err("fork", NULL, true));
	if (pid == 0)
	{
		if (setup_fds(input, msh()->og_fds, true))
			error_exit(NULL, NULL, 1, false);
		cmd = cmd_create(input);
		env = env_list_to_char(msh()->env);
		if (env == NULL)
			return (free(cmd), error_exit("malloc", "Allocation Error", 1, false));
		if (execve(cmd, input->argv, env))
		{
			free(cmd);
			free_arr(env);
			error_exit(NULL, input->argv[0], 1, true);
		}
	}
	wait_child();
}
