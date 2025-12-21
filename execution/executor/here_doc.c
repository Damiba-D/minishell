#include "../../minishell.h"
//#include "../libft/get_next_line/get_next_line.h"
/*
If delimiter is unquoted (double or single, does not matter), expansions are performed normally and \ must used to escape special characters
If any part of delimiter is quoted, everything appears to be treated a string literal
 */

/* int	h_d_handler(t_data cmd_data)
{
	char	*line;
	int		h_d_pipe[2];
	size_t	lim_len;
	size_t	line_len;

	if (pipe(h_d_pipe) == -1)
		return (ft_putstr_fd("pipe error\n", 2), -1);
	lim_len = ft_strlen(cmd_data.argv[2]);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line)
			line_len = ft_strlen(line);
		if (!line || \
(!ft_strncmp(line, cmd_data.argv[2], (lim_len)) && line_len - 1 == lim_len))
		{
			free(line);
			break ;
		}
		write(h_d_pipe[1], line, line_len);
		free(line);
	}
	close(h_d_pipe[1]);
	return (h_d_pipe[0]);
} */

void    here_doc_handler(t_file *here_doc)
{
    char *tmpfilename;
    char *fileno;
    int filenum;
	char *line;
	size_t	del_len;
	char *expanded;

    filenum = 0;
    while (true)
    {
        fileno = ft_itoa(filenum);
		tmpfilename = ft_strjoin(HEREDOC, fileno);
		free(fileno);
		if (!tmpfilename)
			error_exit("malloc", "Allocation Error", 1, false);
        if (access(tmpfilename, F_OK))
        {
			filenum = open(tmpfilename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (filenum == -1)
			{
				free(tmpfilename);
				error_exit(NULL, "cannot create tmp file for here-doc", 1, false);
			}
			break ;
        }
		else
			filenum++;
		free(tmpfilename);
    }
	del_len = ft_strlen(here_doc->filename) + 1;
	while (true)
	{
		line = readline(">");
		if (!line || !ft_strncmp(line, here_doc->filename, del_len))
		{
			free(line);
			break ;
		}
		if (!here_doc->quoted)
		{
			expanded = expand_arg(line);
			free(line);
			ft_putendl_fd(expanded, filenum);
			free(expanded);
		}
		else
		{
			ft_putendl_fd(line, filenum);
			free(line);
		}
	}
	close(filenum);
	free(here_doc->filename);
	here_doc->filename = tmpfilename;
}

/* int main()
{
	t_file var;
	int fd;
	char *line;

	var.filename = "EOF";
	var.quoted = false;
	here_doc_handler(&var);
	fd = open(var.filename, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	close(fd);
	unlink(var.filename);
	free(var.filename);
	exit(0);
} */
