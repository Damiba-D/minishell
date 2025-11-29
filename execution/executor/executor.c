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
		new_fd[0] = open(name, O_RDONLY);
		dup2(new_fd[0], STDIN_FILENO);
		close(new_fd[0]);
	}
	if (input->outfiles->filename)
	{
		og_fd[1] = dup(STDOUT_FILENO);
		new_fd[1] = open(input->outfiles[0].filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
