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

char	*ext_reds_file_single(char *seg, int red_pos, t_tokent type)
{
	int	start_file;

	if(red_pos == -1)
		return (NULL);
	if (type == APPEND || type == HDOC)
		red_pos += 2;
	else
		red_pos += 1;
	start_file = skip_whitespace(seg, red_pos);
	return (ext_reds_file_util(seg, start_file));
}

void	ext_reds_file(char *seg)
{
	t_file	*infiles;
	int		in_count;
	t_file	*outfiles;
	int		out_count;
	int		i;

	count_reds(seg, &in_count, &out_count);
	if (!in_count && !out_count)
		return ;							//no reds, nothing happens
	infiles = malloc(sizeof(t_file) * (in_count + 1));
	outfiles = malloc(sizeof(t_file) * (out_count + 1));
	if (!infiles || !outfiles)
		return (free(infiles), free(outfiles), NULL); //malloc error exit
	infiles[in_count].filename = NULL;
	outfiles[out_count].filename = NULL;
	i = 0;
	while (seg[i])
	{
		//Store everything in the arrays
	}
}

char	*ext_reds_file_util(char *seg, int start_pos)
{
	int		i;
	int		k;
	int		in_quote;
	int		in_dquote;
	char	*res;

	res = malloc(ft_strlen(seg + start_pos) + 1);
	if (!res)
		return (NULL);
	i = start_pos;
	k = 0;
	in_quote = 0;
	in_dquote = 0;
	while (seg[i] && ((in_quote || in_dquote) || seg[i] != ' '))
	{
		update_quotes(seg[i], &in_quote, &in_dquote);
		if ((seg[i] != '\'' && seg[i] != '\"') || (i > 0 && seg[i - 1] == '\\'))
			res[k++] = seg[i];
		i++;
	}
	res[k] = '\0';
	return (res);
}
