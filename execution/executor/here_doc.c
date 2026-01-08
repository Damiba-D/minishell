#include "../../minishell.h"

static void	create_tmp_file(char **filename, int *filenum)
{
	char *fileno;

	*filenum = 0;
	while (true)
	{
		fileno = ft_itoa(*filenum);
		*filename = ft_strjoin(HEREDOC, fileno);
		free(fileno);
		if (!*filename)
			error_exit("malloc", "Allocation Error", 1, false);
		if (access(*filename, F_OK))
		{
			*filenum = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (*filenum == -1)
			{
				free(*filename);
				error_exit("heredoc", "open", 1, true);
			}
			break ;
		}
		else
			*filenum += 1;
		free(*filename);
	}
}

static void write_here_doc(t_file *here_doc, int filefd)
{
	char *line;
	size_t	del_len;
	char *expanded;
	int stdin_backup;

	del_len = ft_strlen(here_doc->filename) + 1;
	msh()->last_exit_status = 0;
	stdin_backup = dup(STDIN_FILENO);
	//potentially here
	while (true)
	{
		line = readline(">");
		if (msh()->hdoc_stop)
		{
			dup2(stdin_backup, STDIN_FILENO);
			close(stdin_backup);
			return ;
		}
		if (!line)
			return (print_hd_error(here_doc->filename));
		if (!ft_strncmp(line, here_doc->filename, del_len))
			return (free(line));
		if (!here_doc->quoted)
		{
			expanded = expand_arg(line);
			ft_putendl_fd(expanded, filefd);
			free(expanded);
		}
		else
			ft_putendl_fd(line, filefd);
		free(line);
	}
}

void    here_doc_handler(t_file *here_doc)
{
    char *tmpfilename;
    int filenum;

	//call signal functions somewhere here, potentially before the readline
	create_tmp_file(&tmpfilename, &filenum);
	setup_hdoc_signals();
	write_here_doc(here_doc, filenum);
	close(filenum);
	setup_interactive_signals();
	free(here_doc->filename);
	here_doc->filename = tmpfilename;
}

