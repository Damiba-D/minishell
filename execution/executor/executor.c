#include "../../minishell.h"
#include "executor.h"

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
	if (fd[0] > 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (fd[1] > 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

/* void execute_pipeline(t_list *inputlst)
{
	int i;
} */

void wait_children(int last_pid)
{
	int i;
	int w_status;

	i = 0;
	while (i < last_pid + 1)
	{
		if (msh()->pids[i] > 0)
			waitpid(msh()->pids[i], &w_status, 0);
		i++;
	}
	if (WIFEXITED(w_status))
		msh()->last_exit_status = WEXITSTATUS(w_status);
	else if (WIFSIGNALED(w_status))
		msh()->last_exit_status = 128 + WTERMSIG(w_status);
	free(msh()->pids);
	msh()->pids = NULL;
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
