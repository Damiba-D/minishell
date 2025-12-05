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
		if (access(infile, R_OK))
			return (msh()->last_exit_status = *flag = 1, infile);
		i++;
	}
	open_file(infile, fd, REDIN);
	return (infile);
}

char *parse_outfiles(t_input *input, int *fd, int *flag)
{
	char	*outfile;
	int		i;

	i = 0;
	outfile = input->outfiles[i].filename;
	if (access(outfile, F_OK) || !access(outfile, W_OK))
		open_file(outfile, fd, input->outfiles[i].mode);
	else
		return (msh()->last_exit_status = *flag = 1, outfile);
	i++;
	while (input->outfiles[i].filename)
	{
		close(*fd);
		outfile = input->outfiles[i].filename;
		if (access(outfile, F_OK) || !access(outfile, W_OK))
			open_file(outfile, fd, input->outfiles[i].mode);
		else
			return (msh()->last_exit_status = *flag = 1, outfile);
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
	if (input->infiles->filename)
	{
		name = parse_infiles(input, &err, &new_fd[0]);
		if (err)
			return (file_err(name), err);
		og_fd[0] = dup(STDIN_FILENO);
		dup2(new_fd[0], STDIN_FILENO);
		close(new_fd[0]);
	}
	if (input->outfiles->filename)
	{
		name = parse_outfiles(input, &new_fd[1], &err);
		if (err)
			return (file_err(name), err);
		og_fd[1] = dup(STDOUT_FILENO);
		dup2(new_fd[1], STDOUT_FILENO);
		close(new_fd[1]);
	}
	return (err);
}

void execute_builtin(t_list *input_node)
{
	t_input	*input;
	int		og_fd[2];

	input = (t_input *)input_node->content;
	if (setup_fds(input, og_fd))
		return ;
	msh()->last_exit_status = run_builtin(input);
	if (input->infiles->filename)
	{
		dup2(og_fd[0], STDIN_FILENO);
		close(og_fd[0]);
	}
	if (input->outfiles->filename)
	{
		dup2(og_fd[1], STDOUT_FILENO);
		close(og_fd[1]);
	}
}

void	executor(void)
{
	t_input *temp;

	temp = (t_input *)msh()->inputlst->content;
	if (is_builtin(temp->argv[0]))
	{
		execute_builtin(msh()->inputlst);
	}
	ft_lstclear(&msh()->inputlst, free_input_node);
}
