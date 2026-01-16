#include "../../minishell.h"
#include "executor.h"

int	setup_fds(t_input *input, int *og_fd, bool save)
{
	int	new_fd[2];
	int	err;

	err = 0;
	if (save)
		save_og_fds(og_fd);
	if (input->infiles->filename)
	{
		parse_infiles(input, &err, &new_fd[0]);
		if (err)
			return (err);
		dup2(new_fd[0], STDIN_FILENO);
		close(new_fd[0]);
	}
	if (input->outfiles->filename)
	{
		parse_outfiles(input, &new_fd[1], &err);
		if (err)
			return (err);
		dup2(new_fd[1], STDOUT_FILENO);
		close(new_fd[1]);
	}
	return (err);
}

void	restore_fds(int *fd)
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

void	close_pipe(void)
{
	close(msh()->pipe[0]);
	close(msh()->pipe[1]);
}

bool	execute_all_hds(t_list *input)
{
	t_list	*current;

	current = input;
	while (current)
	{
		exe_hds((t_input *)current->content);
		if (msh()->hdoc_stop)
		{
			free(msh()->pids);
			msh()->pids = NULL;
			return (false);
		}
		current = current->next;
	}
	return (true);
}
