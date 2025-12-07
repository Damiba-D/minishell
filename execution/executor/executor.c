#include "../../minishell.h"
#include "executor.h"

bool is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "env", 4))
		return (true);
	else if (!ft_strncmp(cmd, "echo", 5))
		return (true);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (true);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (true);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (true);
	else if (!ft_strncmp(cmd, "export", 7))
		return (true);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (true);
	return (false);
}

int run_builtin(t_input *input)
{
	char	*cmd;

	cmd = input->argv[0];
	if (!ft_strncmp(cmd, "env", 4))
		return (env_cmd());
	else if (!ft_strncmp(cmd, "echo", 5))
		return (echo_cmd(input->argv));
	else if (!ft_strncmp(cmd, "unset", 6))
		return (unset_cmd(input->argv));
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (pwd_cmd(input->argv));
	else if (!ft_strncmp(cmd, "cd", 3))
		return (cd_cmd(input->argv));
	else if (!ft_strncmp(cmd, "export", 7))
		return (export_cmd(input->argv));
	else if (!ft_strncmp(cmd, "exit", 5))
		return (exit_cmd(input->argv));
	return (0);
}

void exe_hds(t_input *input)
{
	t_token	type;
	int		i;

	i = 0;
	while (input->infiles[i].filename)
	{
		type = input->infiles[i].mode;
		if (type == HDOC)
			here_doc_handler(&input->infiles[i]);
		i++;
	}
}

void open_file(char *name, int *fd, t_token type)
{
	if (type == REDIN || type == HDOC)
		*fd = open(name, O_RDONLY);
	if (type == REDOUT)
		*fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (type == APPEND)
		*fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

char	*parse_infiles(t_input *input, int *flag, int *fd)
{
	char	*infile;
	int		i;

	i = 0;
	exe_hds(input);
	while (input->infiles[i].filename)
	{
		infile = input->infiles[i].filename;
		open_file(infile, fd, REDIN);
		if (*fd == -1)
			return (msh()->last_exit_status = *flag = 1, infile);
		if (input->infiles[i + 1].filename)
			close(*fd);
		i++;
	}
	return (infile);
}

char *parse_outfiles(t_input *input, int *fd, int *flag)
{
	char	*outfile;
	int		i;

	i = 0;
	while (input->outfiles[i].filename)
	{
		outfile = input->outfiles[i].filename;
		open_file(outfile, fd, input->outfiles[i].mode);
		if (*fd == -1)
			return (msh()->last_exit_status = *flag = 1, outfile);
		if (input->outfiles[i + 1].filename)
			close(*fd);
		i++;
	}
	return (outfile);
}

int	setup_fds(t_input *input, int *og_fd)
{
	int new_fd[2];
	char	*name;
	int		err;

	err = 0;
	og_fd[0] = dup(STDIN_FILENO);
	og_fd[1] = dup(STDOUT_FILENO);
	if (input->infiles->filename)
	{
		name = parse_infiles(input, &err, &new_fd[0]);
		if (err)
			return (print_err(NULL, name, true), err);
		dup2(new_fd[0], STDIN_FILENO);
		close(new_fd[0]);
	}
	if (input->outfiles->filename)
	{
		name = parse_outfiles(input, &new_fd[1], &err);
		if (err)
			return (print_err(NULL, name, true), err);
		dup2(new_fd[1], STDOUT_FILENO);
		close(new_fd[1]);
	}
	return (err);
}

void restore_fds(int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

void execute_builtin(t_input *input)
{
	if (setup_fds(input, msh()->og_fds))
		return (restore_fds(msh()->og_fds));
	msh()->last_exit_status = run_builtin(input);
	restore_fds(msh()->og_fds);
}

void execute_ext_cmd(t_input *input, int cmd_no)
{
	pid_t pid;
	char **env;

	msh()->pids[cmd_no] = fork();
	pid = msh()->pids[cmd_no];
	if (pid == -1)
		return (msh()->last_exit_status = 1, print_err("fork", NULL, true));
	if (pid == 0)
	{
		setup_fds(input, msh()->og_fds);
		env = env_list_to_char(msh()->env);
		if (execve(input->argv[0], input->argv, env))
		{
			free(msh()->pids);
			free_arr(env);
			error_exit(NULL, input->argv[0], 1, true);
		}
	}
}

void wait_children(int last_pid)
{
	int i;

	i = 0;
	while (i < last_pid + 1)
	{
		if (msh()->pids[i] > 0)
			waitpid(msh()->pids[i], &msh()->last_exit_status, 0);
		i++;
	}
	free(msh()->pids);
}

void	executor(void)
{
	t_input *temp;
	bool wait_child;

	temp = (t_input *)msh()->inputlst->content;
	wait_child = false;
	if (ft_lstsize(msh()->inputlst) == 1)
	{
		if (is_builtin(temp->argv[0]))
			execute_builtin(temp);
		else
		{
			msh()->pids = malloc(sizeof(pid_t));
			execute_ext_cmd(temp, 0);
			wait_child = true;
		}
	}
	/* else
	{
		execute_pipeline(msh()->inputlst);
		wait_child = true;
	} */
	if (wait_child)
		wait_children(ft_lstsize(msh()->inputlst) - 1);
	ft_lstclear(&msh()->inputlst, free_input_node);
}
