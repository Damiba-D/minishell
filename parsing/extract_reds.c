#include "../minishellM.h"

static int	count_reds(char *seg, int *in, int *out)
{
	int		i;
	char	type;

	*in = 0;
	*out = 0;
	i = 0;
	while (seg[i])
	{
		if (seg[i] == '<' || seg[i] == '>')
		{
			type = seg[i];
			if (seg[i + 1] == seg[i])
				i++;
			i = skip_whitespace(seg, i + 1);
			if (!seg[i])
				return (1);
			if (type == '<')
				(*in)++;
			else if (type == '>')
				(*out)++;
		}
		else
			i++;
	}
	return (0);
}

char	*ext_reds_file_single(char *seg, int *i, t_input *node, int *red_i)
{
	int 	type;
	char	*filename;

	if (seg[*i] == '<')
		type = REDIN;
	else
		type = REDOUT;
	if (seg[*i + 1] == seg[*i])
	{
		(*i)++;
		type += 2;
	}
	*i = skip_whitespace(seg, *i + 1);
	if (!seg[*i])
		return (NULL);		// ERROR
	if (type == REDIN || type == HDOC)
		node->infiles[*red_i].mode = type;
	else
		node->outfiles[*red_i].mode = type;
	if (type == REDIN || type == HDOC)
		filename = ext_reds_file_util(seg, i, &node->infiles[*red_i].quoted);
	else
		filename = ext_reds_file_util(seg, i, &node->outfiles[*red_i].quoted);
	(*red_i)++;
	return (filename);
}

void	ext_reds_file(char *seg, t_input *node)
{
	int	in_count;
	int	out_count;
	int	i;
	int in_i;
	int out_i;

	count_reds(seg, &in_count, &out_count);
	if (!in_count && !out_count)
		return ;							//no reds, nothing happens
	node->infiles = malloc(sizeof(t_file) * (in_count + 1));
	node->outfiles = malloc(sizeof(t_file) * (out_count + 1));
	if (!node->infiles || !node->outfiles)
		return (free(node->infiles), free(node->outfiles), NULL); //malloc error exit
	node->infiles[in_count].filename = NULL;
	node->outfiles[out_count].filename = NULL;
	i = 0;
	while (seg[i])
	{
		if (seg[i] == '<' || seg[i] == '>')
		{
		}
		else
			i++;
	}
}

char	*ext_reds_file_util(char *seg, int *i, bool *quoted)
{
	int		k;
	int		in_quote;
	int		in_dquote;
	char	*res;

	k = 0;
	in_quote = 0;
	in_dquote = 0;
	res = malloc(ft_strlen(seg + *i) + 1);
	if (!res)
		return (NULL);
	while (seg[*i] && ((in_quote || in_dquote) || seg[*i] != ' '))
	{
		update_quotes(seg[*i], &in_quote, &in_dquote);
		if (in_quote || in_dquote)
			*quoted = true;
		if ((seg[*i] != '\'' && seg[*i] != '\"') || (*i > 0 && seg[*i - 1] == '\\'))
			res[k++] = seg[*i];
		(*i)++;
	}
	res[k] = '\0';
	return (res);
}
