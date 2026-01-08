#include "../../minishell.h"
#include "executor.h"

void exe_hds(t_input *input)
{
	t_token	type;
	int		i;
	int stdin_backup;

	i = 0;
	stdin_backup = dup(STDIN_FILENO);
	while (input->infiles[i].filename)
	{
		type = input->infiles[i].mode;
		if (type == HDOC)
			here_doc_handler(&input->infiles[i]);
		if (msh()->hdoc_stop)
		{
			dup2(stdin_backup, STDIN_FILENO);
			break ;
		}
		i++;
	}
	close(stdin_backup);
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

void save_og_fds(int *og_fd)
{
	og_fd[0] = dup(STDIN_FILENO);
	og_fd[1] = dup(STDOUT_FILENO);
}


