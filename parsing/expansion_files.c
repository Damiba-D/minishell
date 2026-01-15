#include "../minishell.h"

static void	expand_file(t_file *file)
{
	char	*expanded;

	if (!file || !file->filename)
		return ;
	expanded = expand_arg(file->filename);
	if (!expanded)
		expanded = ft_strdup("");
	free(file->filename);
	file->filename = expanded;
}

void	expand_files(t_input *node)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	while (node->infiles && node->infiles[i].filename)
	{
		if (node->infiles[i].mode != HDOC || !node->infiles[i].quoted)
			expand_file(&node->infiles[i]);
		i++;
	}
	i = 0;
	while (node->outfiles && node->outfiles[i].filename)
	{
		expand_file(&node->outfiles[i]);
		i++;
	}
}
