#include "../minishell.h"

char	*remove_all_reds(char *seg)
{
	char	*cleaned;
	int		src_i;
	int		dst_i;
	int		in_single;
	int		in_double;

	src_i = 0;
	dst_i = 0;
	in_single = 0;
	in_double = 0;
	cleaned = malloc(ft_strlen(seg) + 1);
	if (!cleaned)
		return (NULL);
	while (seg[src_i])
	{
		update_quotes(seg[src_i], &in_single, &in_double);
		if (!in_single && !in_double
			&& ((seg[src_i] == '<') || (seg[src_i] == '>')))
			src_i = skip_reds_filename(seg, src_i);
		else
			cleaned[dst_i++] = seg[src_i++];
	}
	cleaned[dst_i] = '\0';
	return (cleaned);
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	clean_heredoc(char *filename)
{
	if (!ft_strncmp(HEREDOC, filename, H_D_LEN))
		unlink(filename);
}

void	free_file_arr(t_file *files)
{
	int	i;

	if (!files)
		return ;
	i = 0;
	while (files[i].filename)
	{
		if (files[i].mode == HDOC)
			clean_heredoc(files[i].filename);
		free(files[i].filename);
		i++;
	}
	free(files);
}

void	free_input_node(void *content)
{
	t_input	*input;

	input = (t_input *)content;
	if (input->argv)
		free_arr(input->argv);
	if (input->infiles)
		free_file_arr(input->infiles);
	if (input->outfiles)
		free_file_arr(input->outfiles);
	free(input);
}
