#include "../../minishell.h"

static bool is_builtin(char *cmd)
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

static int run_builtin(t_input *input)
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

static void exe_hds(t_input *input)
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

static char	*parse_infiles(t_input *input)
{
	char	*infile;
	int		i;

	i = 0;
	exe_hds(input);
	while (input->infiles[i].filename)
	{
		infile = input->infiles[i].filename;
		if (access(infile, R_OK))
			return (NULL);
		i++;
	}
	return (infile);
}

static void open_file(char *name, int *fd, t_token type)
{
	if (type == REDIN || type == HDOC)
		*fd = open(name, O_RDONLY);
	if (type == REDOUT)
		*fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (type == APPEND)
		*fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

static char *parse_outfiles(t_input *input, int *fd)
{
	char	*outfile;
	int		i;

	i = 0;
	outfile = input->outfiles[i].filename;
	if (access(outfile, F_OK) || !access(outfile, W_OK))
		open_file(outfile, fd, input->outfiles[i].mode);
	else
		return (NULL);
	i++;
	while (input->outfiles[i].filename)
	{
		close(*fd);
		outfile = input->outfiles[i].filename;
		if (access(outfile, F_OK) || !access(outfile, W_OK))
			open_file(outfile, fd, input->outfiles[i].mode);
		else
			return (NULL);
		i++;
	}
	return (outfile);
}

static void	setup_fds(t_list *input_node, int *og_fd)
{
	t_input *input;
	int new_fd[2];
	char	*name;

	input = (t_input *)input_node->content;
	if (input->infiles->filename)
	{
		name = parse_infiles(input);
		og_fd[0] = dup(STDIN_FILENO);
		open_file(name, &new_fd[0], REDIN);
		dup2(new_fd[0], STDIN_FILENO);
		close(new_fd[0]);
	}
	if (input->outfiles->filename)
	{
		name = parse_outfiles(input, &new_fd[1]);
		og_fd[1] = dup(STDOUT_FILENO);
		dup2(new_fd[1], STDOUT_FILENO);
		close(new_fd[1]);
	}
}

static void execute_builtin(t_list *input_node)
{
	t_input	*input;
	int		og_fd[2];

	input = (t_input *)input_node->content;
	setup_fds(input_node, og_fd);
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
