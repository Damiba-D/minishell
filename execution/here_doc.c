#include "../minishell.h"
#include "libft/get_next_line/get_next_line.h"
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

    filenum = 0;
    while (true)
    {
        fileno = ft_itoa(filenum);
		tmpfilename = ft_strjoin("/tmp/minishell-heredoc-", fileno);
		free(fileno);
		if (!tmpfilename)
			exit(1);
        if (access(tmpfilename, F_OK))
        {
			filenum = open(tmpfilename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			break ;
        }
		else
			filenum++;
		free(tmpfilename);
    }
	while (true)
	{
		line = readline(">");
		if (!line && ft_strncmp(line, here_doc->filename, ft_strlen(here_doc->filename)))
		{

		}
	}
	close(filenum);
	filenum = open(tmpfilename, O_RDONLY);
	close(filenum);
	unlink(tmpfilename);
	free(tmpfilename);
}

int main()
{
	t_file var;

	var.filename = "EOF";
	var.quoted = false;
	here_doc_handler(&var);
	exit(0);
}
